#include "n64_controller.h"

struct n64_controller {
	n64_controller_type controller_type;
	n64_extension       extension;

	struct n64_controller_data *current;
	struct n64_controller_data *next;

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

	uint32_t bit_pos;
};
