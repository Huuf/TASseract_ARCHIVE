#ifndef __RA8875_H
#define __RA8875_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "stm32h7xx_hal.h"
#include "stm32h745xx.h"
#include <stdbool.h>

struct ra8875_state;

typedef enum ra8875_result {
	RA8875_OK = 0,
	RA8875_INVALID_POINTER = 1,
	RA8875_SPI_ERROR = 2,
} ra8875_result;

ra8875_result ra8875_initialize(struct ra8875_state **state_pointer, SPI_HandleTypeDef *spi_port, GPIO_TypeDef *RST_PORT, uint16_t RST_PIN,
	GPIO_TypeDef *INT_PORT, uint16_t INT_PIN, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN);
ra8875_result ra8875_destroy(struct ra8875_state **state_pointer);
ra8875_result ra8875_turn_on_display(struct ra8875_state *ra8875, bool on);
ra8875_result ra8875_gpiox(struct ra8875_state *ra8875, bool state);
ra8875_result ra8875_pwm1_setup(struct ra8875_state *ra8875, bool on, uint8_t divider);
ra8875_result ra8875_pwm1_duty_cycle(struct ra8875_state *ra8875, uint8_t cycle);

void ra8875_set_graphics_mode(struct ra8875_state *ra8875);
void ra8875_draw_rectangle(struct ra8875_state *ra8875, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool outline);
void ra8875_draw_line(struct ra8875_state *ra8875, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ra8875_set_text_mode(struct ra8875_state *ra8875);
void ra8875_set_text_cursor(struct ra8875_state *ra8875, uint16_t x, uint16_t y);
void ra8875_set_text_color(struct ra8875_state *ra8875, uint16_t foreground, uint16_t background);
void ra8875_set_text_transparent(struct ra8875_state *ra8875, uint16_t foreground);
void ra8875_set_text_enlarge(struct ra8875_state *ra8875, uint8_t scale);
void ra8875_text_Write(struct ra8875_state *ra8875, const char* buffer);

void ra8875_enable_touch(struct ra8875_state *ra8875);
void ra8875_disable_touch(struct ra8875_state *ra8875);
bool ra8875_read_touch(struct ra8875_state *ra8875, uint16_t *x, uint16_t *y);
#ifdef __cplusplus
}
#endif

#endif /* __RA8875_H */
