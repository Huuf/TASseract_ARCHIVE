#ifndef __GC_CONTROLLER_H
#define __GC_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

struct __attribute__((packed)) gamecube_controller_data
{
	uint8_t a : 1;
	uint8_t b : 1;
	uint8_t x : 1; // 1 bit wide
	uint8_t y : 1;
	uint8_t start : 1;
	uint8_t beginning_zeros : 3;

    uint8_t d_left : 1;
    uint8_t d_right : 1;
    uint8_t d_down : 1;
    uint8_t d_up : 1;
    uint8_t z : 1;
    uint8_t r : 1;
    uint8_t l : 1;
    uint8_t beginning_one : 1;

    int8_t a_x_axis;
    int8_t a_y_axis;
    int8_t c_x_axis;
    int8_t c_y_axis;
    uint8_t l_trigger;
    uint8_t r_trigger;
};

typedef enum gamecube_controller_type {
	gamecube_controller_to_console,
	gamecube_controller_to_visualization,
	gamecube_controller_to_controller
} gamecube_controller_type;

struct gamecube_controller;

bool gamecube_controller_setup(struct gamecube_controller **controller, gamecube_controller_type controller_type,
	GPIO_TypeDef *DATA_PORT, uint16_t DATA_PIN, GPIO_TypeDef *VCC_RUMBLE_PORT, uint16_t VCC_RUMBLE_PIN,
	GPIO_TypeDef *VCC_PORT, uint16_t VCC_PIN, bool is_four_score);
bool gamecube_controller_set_data(struct gamecube_controller *controller, struct gamecube_controller_data *data);
void gamecube_controller_tick(struct gamecube_controller *controller);
bool gamecube_controller_destroy(struct gamecube_controller **controller);


#ifdef __cplusplus
}
#endif

#endif /* __GC_CONTROLLER_H */
