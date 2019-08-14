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

	bool is_four_score;
	uint32_t bit_pos;
};
