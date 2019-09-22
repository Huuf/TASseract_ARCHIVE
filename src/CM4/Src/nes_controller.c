#include "nes_controller.h"

struct nes_controller {
	nes_controller_type controller_type;

	struct nes_controller_data *current;
	struct nes_controller_data *next;

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
};

void setup_to_console(struct nes_controller *controller);
void setup_to_visualisation(struct nes_controller *controller);
void setup_to_controller(struct nes_controller *controller);
void setup_pin_input(GPIO_TypeDef *port, uint16_t pin, bool pullUp);
void setup_pin_output(GPIO_TypeDef *port, uint16_t pin, bool high);

bool nes_controller_setup(struct nes_controller **controller_ptr, nes_controller_type controller_type,
	GPIO_TypeDef *CLK_PORT, uint16_t CLK_PIN, GPIO_TypeDef *OUT_PORT, uint16_t OUT_PIN,
	GPIO_TypeDef *D0_PORT, uint16_t D0_PIN, GPIO_TypeDef *D3_PORT, uint16_t D3_PIN,
	GPIO_TypeDef *D4_PORT, uint16_t D4_PIN, GPIO_TypeDef *VCC_PORT, uint16_t VCC_PIN,
	bool is_four_score)
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

	is_four_score = is_four_score;

	switch (controller_type) {
		case nes_controller_to_console:
			setup_to_console(controller_type);
			break;
		case nes_controller_to_visualization:
			setup_to_visualization(controller_type);
			break;
		case nes_controller_to_controller:
			setup_to_controller(controller_type);
			break;
	}

	return true;
}

void setup_to_console(struct nes_controller *controller)
{
	setup_pin_input(controller->VCC_PORT, controller->VCC_PIN, GPIO_NOPULL);
	setup_pin_input(controller->CLK_PORT, controller->CLK_PIN, GPIO_NOPULL);
	setup_pin_input(controller->OUT_PORT, controller->OUT_PIN, GPIO_NOPULL);
	setup_pin_output(controller->D0_PORT, controller->D0_PIN, GPIO_PULLUP, true, true);
	setup_pin_output(controller->D3_PORT, controller->D3_PIN, GPIO_PULLUP, true, true);
	setup_pin_output(controller->D4_PORT, controller->D4_PIN, GPIO_PULLUP, true, true);
}

void setup_to_visualisation(struct nes_controller *controller)
{
	setup_pin_input(controller->VCC_PORT, controller->VCC_PIN, GPIO_NOPULL);
	setup_pin_output(controller->CLK_PORT, controller->CLK_PIN, GPIO_NOPULL, true, true);
	setup_pin_output(controller->OUT_PORT, controller->OUT_PIN, GPIO_NOPULL, true, true);
	setup_pin_output(controller->D0_PORT, controller->D0_PIN, GPIO_PULLUP, true, true);
	setup_pin_output(controller->D3_PORT, controller->D3_PIN, GPIO_PULLUP, true, true);
	setup_pin_output(controller->D4_PORT, controller->D4_PIN, GPIO_PULLUP, true, true);
}

void setup_to_controller(struct nes_controller *controller)
{
	setup_pin_input(controller->VCC_PORT, controller->VCC_PIN, GPIO_NOPULL);
	setup_pin_output(controller->CLK_PORT, controller->CLK_PIN, GPIO_PULLUP, true, true);
	setup_pin_output(controller->OUT_PORT, controller->OUT_PIN, GPIO_PULLUP, true, true);
	setup_pin_input(controller->D0_PORT, controller->D0_PIN, GPIO_NOPULL);
	setup_pin_input(controller->D3_PORT, controller->D3_PIN, GPIO_NOPULL);
	setup_pin_input(controller->D4_PORT, controller->D4_PIN, GPIO_NOPULL);
}

void setup_pin_input(GPIO_TypeDef *port, uint16_t pin, uint32_t pull)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(SNES_RESET_GPIO_Port, &GPIO_InitStruct);
	port->BSRR = pin << 16;
}

void setup_pin_output(GPIO_TypeDef *port, uint16_t pin, uint32_t pull, bool open_drain, bool high)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = open_drain ? GPIO_MODE_OUTPUT_OD : GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(SNES_RESET_GPIO_Port, &GPIO_InitStruct);
	if (high)
		port->BSRR = pin;
	else
		port->BSRR = pin << 16;
}
