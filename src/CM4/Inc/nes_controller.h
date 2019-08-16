#ifndef __NES_CONTROLLER_H
#define __NES_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct __attribute__((packed)) nes_controller_data {
	uint8_t right : 1; // low bit
	uint8_t left : 1;
	uint8_t down : 1;
	uint8_t up : 1;
	uint8_t start : 1;
	uint8_t select : 1;
	uint8_t b : 1;
	uint8_t a : 1; // high bit
};

typedef enum nes_controller_type {
	nes_controller_to_console,
	nes_controller_to_visualization,
	nes_controller_to_controller
} nes_controller_type;

struct nes_controller;

bool nes_controller_setup(struct nes_controller **controller_ptr, nes_controller_type controller_type,
	GPIO_TypeDef *CLK_PORT, uint16_t CLK_PIN, GPIO_TypeDef *OUT_PORT, uint16_t OUT_PIN,
	GPIO_TypeDef *D0_PORT, uint16_t D0_PIN, GPIO_TypeDef *D3_PORT, uint16_t D3_PIN,
	GPIO_TypeDef *D4_PORT, uint16_t D4_PIN, GPIO_TypeDef *VCC_PORT, uint16_t VCC_PIN,
	bool is_four_score);
bool nes_controller_get_data(struct nes_controller *controller, struct nes_controller_data *data);
bool nes_controller_set_data(struct nes_controller *controller, struct nes_controller_data *data);
void nes_controller_tick(struct nes_controller *controller);
bool nes_controller_destroy(struct nes_controller **controller_ptr);
void nes_controller_clone_to(struct nes_controller *controller, nes_controller *clone_to);
void nes_controller_stop_sending(struct nes_controller *controller);

#ifdef __cplusplus
}
#endif

#endif /* __NES_CONTROLLER_H */
