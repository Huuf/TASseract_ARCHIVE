#ifndef __NES_H
#define __NES_H

#include "nes_controller.h"

#ifdef __cplusplus
extern "C" {
#endif

struct nes;

void nes_setup(struct nes **nes_ptr,
	struct nes_controller *p1, struct nes_controller *p2,
	struct nes_controller *v1, struct nes_controller *v2,
	bool has_vhsync_interrupt);
void nes_tick(struct nes *nes);
void nes_vsync(struct nes *nes);
void nes_hsync(struct nes *nes);
void nes_destroy(struct nes **nes_ptr);

void nes_process_data(struct nes *nes, uint8_t *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __NES_H */
