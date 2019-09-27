#ifndef __NES_CONTROLLER_H
#define __NES_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32h745xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Data that gets send to/from the actual console
/// @details All fields are 1 when released and 0 when pressed
struct __attribute__((packed)) nes_controller_data {
	uint8_t right : 1;  ///< D-Pad Right
	uint8_t left : 1;   ///< D-Pad Left
	uint8_t down : 1;   ///< D-Pad Down
	uint8_t up : 1;     ///< D-Pad Up
	uint8_t start : 1;  ///< Start Button
	uint8_t select : 1; ///< Select Button
	uint8_t b : 1;      ///< B Button
	uint8_t a : 1;      ///< A Button
};

/// @brief The functionality for the controller
typedef enum nes_controller_type {
	nes_controller_to_console,       ///< For sending to the console, simulating a controller
	nes_controller_to_visualization, ///< For sending to the visualization board
	nes_controller_to_controller     ///< For reading from a controller
} nes_controller_type;

/// @brief The NES Controller data for internal status
struct nes_controller;

/// @brief Initialize the NES Controller
/// @details Setups the pins for input/output, correct state and all other functions.
/// @param[out] controller_ptr New ::nes_controller instance
/// @param[in] controller_type The ::nes_controller_type to initialize this port as
/// @param[in] CLK_PORT The ::GPIO_TypeDef port for the clock line
/// @param[in] CLK_PIN The pin of the clock line
/// @param[in] OUT_PORT The ::GPIO_TypeDef port for the out/latch line
/// @param[in] OUT_PIN The pin of the out/latch line
/// @param[in] D0_PORT The ::GPIO_TypeDef port for the data 0 line
/// @param[in] D0_PIN The pin of the data 0 line
/// @param[in] D3_PORT The ::GPIO_TypeDef port for the data 3 line
/// @param[in] D3_PIN The pin of the data 3 line
/// @param[in] D4_PORT The ::GPIO_TypeDef port for the data 4 line
/// @param[in] D4_PIN The pin of the data 4 line
/// @param[in] VCC_PORT The ::GPIO_TypeDef port for the vcc/power line
/// @param[in] VCC_PIN The pin of the vcc/power line
/// @param[in] clock_fix The number of 0.25us ticks to wait before setting the data pins
/// @param[in] dpcm_fix Keep the last latch in memory?
/// @param[in] is_four_score If the controller needs to simulate a four score device
/// @returns If the creation of the controller succeeded
bool nes_controller_setup(struct nes_controller **controller_ptr, nes_controller_type controller_type,
	GPIO_TypeDef *CLK_PORT, uint16_t CLK_PIN, GPIO_TypeDef *OUT_PORT, uint16_t OUT_PIN,
	GPIO_TypeDef *D0_PORT, uint16_t D0_PIN, GPIO_TypeDef *D3_PORT, uint16_t D3_PIN,
	GPIO_TypeDef *D4_PORT, uint16_t D4_PIN, GPIO_TypeDef *VCC_PORT, uint16_t VCC_PIN,
	uint8_t clock_fix, bool dpcm_fix, bool is_four_score);
/// @brief Frees the given controller and sets the pins back to their initial state
/// @param[in] controller_ptr The ::nes_controller instance to be freed
void nes_controller_destroy(struct nes_controller **controller_ptr);
/// @brief Does a tick of information transmission for the controller
/// @details When receiving it's after the last bit received, for sending it's after the last bit
///    has been sent.
/// @param[in] controller The ::nes_controller to send/receive data to/from
/// @returns If a complete controller package has been sent
bool nes_controller_tick(struct nes_controller *controller);
/// @brief Gets the last data from the controller
/// @details Make sure to call after ::nes_controller_tick returns true for full data, else you will
///   get incomplete or corrupt data
/// @param[in] controller The ::nes_controller to get the data from
/// @param[in,out] data The ::nes_controller_data to retrieve, when a fourscore, make sure to allow
///    for 2 sequentially in memory
/// @returns If successful
bool nes_controller_get_data(struct nes_controller *controller, struct nes_controller_data *data);
/// @brief Sets the next data to be send
/// @details Make sure to call after ::nes_controller_tick returns true, else it will switch buttons
///   during the actual transmission.
/// @param[in] controller The ::nes_controller to set the next data to
/// @param[in] data The ::nes_controller_data to send next
/// @returns If successful
bool nes_controller_set_data(struct nes_controller *controller, struct nes_controller_data *data);
/// @brief Clones the data from the current controller to a different port
/// @details The ::nes_controller_type must be set to ::nes_controller_to_controller
/// @param[in] controller The ::nes_controller to clone from
/// @param[in] clone_to The ::nes_controller to clone to
void nes_controller_clone_to(struct nes_controller *controller, struct nes_controller *clone_to);
/// @brief Stops sending data to the ::nes_controller sending it as all unpressed
/// @param[in] controller The controller instance;
void nes_controller_stop_sending(struct nes_controller *controller);

#ifdef __cplusplus
}
#endif

#endif /* __NES_CONTROLLER_H */
