#ifndef __NES_H
#define __NES_H

#include "nes_controller.h"

#ifdef __cplusplus
extern "C" {
#endif

struct nes;

void nes_setup(struct nes **nes_ptr, struct nes_controller *p1, struct nes_controller *p2, bool has_vhsync_interrupt);
void nes_tick(struct nes *nes);
void nes_vsync(struct nes *nes);
void nes_hsync(struct nes *nes);
void nes_destroy(struct nes **nes_ptr);

void nes_process_serial_protocol_insert_name_here(struct nes *nes, uint8_t *data, size_t size);
void nes_process_bk2_frame(struct nes *nes, uint8_t *data, size_t size);
void nes_process_fm2_frame(struct nes *nes, uint8_t *data, size_t size);
void nes_process_fm3_frame(struct nes *nes, uint8_t *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __NES_H */
