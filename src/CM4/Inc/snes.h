#ifndef __SNES_H
#define __SNES_H

#ifdef __cplusplus
extern "C" {
#endif

struct snes;

void snes_setup(struct snes **snes_ptr, struct snes_controller *p1, struct snes_controller *p2, bool has_vhsync_interrupt);
void snes_tick(struct snes *snes);
void snes_vsync(struct snes *snes);
void snes_hsync(struct snes *snes);
void snes_destroy(struct snes **snes_ptr);

void snes_process_serial_protocol_insert_name_here(struct snes *snes, uint8_t *data, size_t size);
void snes_process_bk2_frame(struct snes *snes, uint8_t *data, size_t size);
void snes_process_lsmv_frame(struct snes *snes, uint8_t *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __SNES_H */
