#ifndef __RA8875_H
#define __RA8875_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "stm32h7xx_hal.h"
#include "stm32h745xx.h"

struct ra8875_state;

typedef enum ra8875_result {
	RA8875_OK = 0,
	RA8875_INVALID_POINTER = 1,
	RA8875_SPI_ERROR = 2,
} ra8875_result;

ra8875_result ra8875_initialize(struct ra8875_state **state_pointer, SPI_HandleTypeDef *spi_port, GPIO_TypeDef *RST_PORT, uint16_t RST_PIN, GPIO_TypeDef *INT_PORT, uint16_t INT_PIN);
ra8875_result ra8875_destroy(struct ra8875_state **state_pointer);

#ifdef __cplusplus
}
#endif

#endif /* __RA8875_H */
