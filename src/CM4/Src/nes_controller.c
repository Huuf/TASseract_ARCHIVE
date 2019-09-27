#include "nes_controller.h"

#include <stddef.h>
#include <stdlib.h>

#include "stm32h7xx_hal.h"

struct nes_controller {
	nes_controller_type controller_type;

	struct nes_controller_data current[2];

	GPIO_TypeDef *CLK_PORT;
	uint16_t      CLK_PIN;
	GPIO_TypeDef *OUT_PORT;
	uint16_t      OUT_PIN;
	GPIO_TypeDef *D0_PORT;
	uint16_t      D0_PIN;
	GPIO_TypeDef *D3_PORT;
	uint16_t      D3_PIN;
	GPIO_TypeDef *D4_PORT;
	uint16_t      D4_PIN;
	GPIO_TypeDef *VCC_PORT;
	uint16_t      VCC_PIN;

	struct nes_controller *clone_to;

	bool is_four_score;

	uint32_t bit_pos;
	bool dpcm_fix;
	uint32_t clock_fix;
};

static void setup_pin_input(GPIO_TypeDef *port, uint16_t pin, uint32_t pull)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(port, &GPIO_InitStruct);
	port->BSRR = pin << 16;
}

static void setup_pin_output(GPIO_TypeDef *port, uint16_t pin, uint32_t pull, bool open_drain, bool high)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = open_drain ? GPIO_MODE_OUTPUT_OD : GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(port, &GPIO_InitStruct);
	if (high)
		port->BSRR = pin;
	else
		port->BSRR = pin << 16;
}

static void setup_to_console(struct nes_controller *controller)
{
	setup_pin_input(controller->VCC_PORT, controller->VCC_PIN, GPIO_NOPULL);
	setup_pin_input(controller->CLK_PORT, controller->CLK_PIN, GPIO_NOPULL);
	setup_pin_input(controller->OUT_PORT, controller->OUT_PIN, GPIO_NOPULL);
	setup_pin_output(controller->D0_PORT, controller->D0_PIN, GPIO_PULLUP, true, false);
	setup_pin_output(controller->D3_PORT, controller->D3_PIN, GPIO_PULLUP, true, false);
	setup_pin_output(controller->D4_PORT, controller->D4_PIN, GPIO_PULLUP, true, false);
}

static void setup_to_visualization(struct nes_controller *controller)
{
	setup_pin_input(controller->VCC_PORT, controller->VCC_PIN, GPIO_NOPULL);
	setup_pin_output(controller->CLK_PORT, controller->CLK_PIN, GPIO_NOPULL, false, false);
	setup_pin_output(controller->OUT_PORT, controller->OUT_PIN, GPIO_NOPULL, false, false);
	setup_pin_output(controller->D0_PORT, controller->D0_PIN, GPIO_NOPULL, false, false);
	setup_pin_output(controller->D3_PORT, controller->D3_PIN, GPIO_NOPULL, false, false);
	setup_pin_output(controller->D4_PORT, controller->D4_PIN, GPIO_NOPULL, false, false);
}

static void setup_to_controller(struct nes_controller *controller)
{
	setup_pin_input(controller->VCC_PORT, controller->VCC_PIN, GPIO_NOPULL);
	setup_pin_output(controller->CLK_PORT, controller->CLK_PIN, GPIO_PULLUP, true, true);
	setup_pin_output(controller->OUT_PORT, controller->OUT_PIN, GPIO_PULLUP, true, true);
	setup_pin_input(controller->D0_PORT, controller->D0_PIN, GPIO_NOPULL);
	setup_pin_input(controller->D3_PORT, controller->D3_PIN, GPIO_NOPULL);
	setup_pin_input(controller->D4_PORT, controller->D4_PIN, GPIO_NOPULL);
}

bool nes_controller_setup(struct nes_controller **controller_ptr, nes_controller_type controller_type,
	GPIO_TypeDef *CLK_PORT, uint16_t CLK_PIN, GPIO_TypeDef *OUT_PORT, uint16_t OUT_PIN,
	GPIO_TypeDef *D0_PORT, uint16_t D0_PIN, GPIO_TypeDef *D3_PORT, uint16_t D3_PIN,
	GPIO_TypeDef *D4_PORT, uint16_t D4_PIN, GPIO_TypeDef *VCC_PORT, uint16_t VCC_PIN,
	uint8_t clock_fix, bool dpcm_fix, bool is_four_score)
{
	if ((controller_ptr == NULL) || (*controller_ptr != NULL)) return false;

	*controller_ptr = calloc(1, sizeof(struct nes_controller));
	if (*controller_ptr == NULL) return false;

	struct nes_controller *controller = *controller_ptr;
	controller->controller_type = controller_type;
	controller->CLK_PORT = CLK_PORT;
	controller->CLK_PIN = CLK_PIN;
	controller->OUT_PORT = OUT_PORT;
	controller->OUT_PIN = OUT_PIN;
	controller->D0_PORT = D0_PORT;
	controller->D0_PIN = D0_PIN;
	controller->D3_PORT = D3_PORT;
	controller->D3_PIN = D3_PIN;
	controller->D4_PORT = D4_PORT;
	controller->D4_PIN = D4_PIN;
	controller->VCC_PORT = VCC_PORT;
	controller->VCC_PIN = VCC_PIN;

	controller->dpcm_fix = dpcm_fix;
	controller->clock_fix = clock_fix * 1; //TODO Change 1 to 0.25us ticks needed;

	is_four_score = is_four_score;

	switch (controller_type) {
		case nes_controller_to_console:
			setup_to_console(controller);
			break;
		case nes_controller_to_visualization:
			setup_to_visualization(controller);
			break;
		case nes_controller_to_controller:
			setup_to_controller(controller);
			break;
	}

	return true;
}

static void reset_pin(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void nes_controller_destroy(struct nes_controller **controller_ptr)
{
	if ((controller_ptr == NULL) || (*controller_ptr == NULL)) return;
	struct nes_controller *controller = *controller_ptr;
	reset_pin(controller->VCC_PORT, controller->VCC_PIN);
	reset_pin(controller->CLK_PORT, controller->CLK_PIN);
	reset_pin(controller->OUT_PORT, controller->OUT_PIN);
	reset_pin(controller->D0_PORT, controller->D0_PIN);
	reset_pin(controller->D3_PORT, controller->D3_PIN);
	reset_pin(controller->D4_PORT, controller->D4_PIN);
	free(controller);
	*controller_ptr = NULL;
}
