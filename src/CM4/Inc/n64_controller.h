#ifndef __N64_CONTROLLER_H
#define __N64_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct __attribute__((packed)) n64_controller_data
{
	uint8_t right : 1; // low bit of 1st byte
	uint8_t left : 1;
	uint8_t down : 1;
	uint8_t up : 1;
	uint8_t start : 1;
	uint8_t z : 1;
	uint8_t b : 1;
	uint8_t a : 1; // high bit of 1st byte

	uint8_t c_right : 1;
	uint8_t c_left : 1;
	uint8_t c_down : 1;
	uint8_t c_up : 1;
	uint8_t r : 1;
    uint8_t l : 1;
    uint8_t dummy1 : 1;
    uint8_t dummy2 : 1;

    int8_t x_axis;

    int8_t y_axis;

};

typedef enum n64_controller_type {
	n64_controller_to_console = 1,
	n64_controller_to_visualization = 2,
	n64_controller_to_controller = 3,
} n64_controller_type;

typedef enum n64_extension {
	n64_extension_none = 0,
	n64_extension_memory = 1,
	n64_extension_rumble = 2,
} n64_extension;

struct n64_controller;

bool n64_controller_setup(struct n64_controller **controller, n64_controller_type controller_type, n64_extension extension,
	GPIO_TypeDef *DATA_PORT, uint16_t DATA_PIN, GPIO_TypeDef *VCC_PORT, uint16_t VCC_PIN,
	bool is_four_score);
bool n64_controller_set_data(struct n64_controller *controller, struct n64_controller_data *data);
void n64_controller_tick(struct n64_controller *controller);
bool n64_controller_destroy(struct n64_controller **controller);


struct n64_controller {
	GPIO_TypeDef *DATA_PORT;
	uint16_t      DATA_PIN;
	GPIO_TypeDef *VCC_PORT;
	uint16_t      VCC_PIN;
};

#ifdef __cplusplus
}
#endif

#endif /* __N64_CONTROLLER_H */
