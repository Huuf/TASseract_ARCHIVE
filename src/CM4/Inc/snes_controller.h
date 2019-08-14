#ifndef __SNES_CONTROLLER_H
#define __SNES_CONTROLLER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct __attribute__((packed)) snes_controller_data {
	// first byte
	uint8_t right : 1; // low bit
	uint8_t left : 1;
	uint8_t down : 1;
	uint8_t up : 1;
	uint8_t start : 1;
	uint8_t select : 1;
	uint8_t y : 1;
	uint8_t b : 1; // high bit

	// second byte
	uint8_t four : 1; // low bit
	uint8_t three : 1;
	uint8_t two : 1;
	uint8_t one : 1;
	uint8_t r : 1;
	uint8_t l : 1;
	uint8_t x : 1;
	uint8_t a : 1; // high bit
};

typedef enum snes_controller_type {
	snes_controller_to_console,
	snes_controller_to_visualization,
	snes_controller_to_controller
} snes_controller_type;

struct snes_controller;

bool snes_controller_setup(struct snes_controller **controller, snes_controller_type controller_type,
	GPIO_TypeDef *CLK_PORT, uint16_t CLK_PIN, GPIO_TypeDef *LAT_PORT, uint16_t LAT_PIN,
	GPIO_TypeDef *D0_PORT, uint16_t D0_PIN, GPIO_TypeDef *D1_PORT, uint16_t D1_PIN,
	GPIO_TypeDef *IO_PORT, uint16_t IO_PIN, GPIO_TypeDef *VCC_PORT, uint16_t VCC_PIN,
	bool is_multitap);
bool snes_controller_set_data(struct snes_controller *controller, struct snes_controller_data *data);
void snes_controller_tick(struct snes_controller *controller);
bool snes_controller_destroy(struct snes_controller **controller);

#ifdef __cplusplus
}
#endif

#endif /* __SNES_CONTROLLER_H */
