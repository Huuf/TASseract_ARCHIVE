#include "snes_controller.h"

struct snes_controller {
	snes_controller_type controller_type

	struct snes_controller_data *current;
	struct snes_controller_data *next;

	GPIO_TypeDef *CLK_PORT;
	uint16_t      CLK_PIN;
	GPIO_TypeDef *LAT_PORT;
	uint16_t      LAT_PIN;
	GPIO_TypeDef *D0_PORT;
	uint16_t      D0_PIN;
	GPIO_TypeDef *D1_PORT;
	uint16_t      D1_PIN;
	GPIO_TypeDef *IO_PORT;
	uint16_t      IO_PIN;
	GPIO_TypeDef *VCC_PORT;
	uint16_t      VCC_PIN;

	bool          is_multitap;
};
