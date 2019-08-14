#include "gc_controller.h"

struct gamecube_controller {
	GPIO_TypeDef *DATA_PORT;
	uint16_t      DATA_PIN;
	GPIO_TypeDef *VCC_RUMBLE_PORT;
	uint16_t      VCC_RUMBLE_PIN;
	GPIO_TypeDef *VCC_PORT;
	uint16_t      VCC_PIN;
};
