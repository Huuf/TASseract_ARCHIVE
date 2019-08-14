#ifndef __GC_H
#define __GC_H

#ifdef __cplusplus
extern "C" {
#endif

//dtm


struct gamecube;

void gamecube_setup(struct gamecube **gamecube_ptr, struct gamecube_controller *p1, struct gamecube_controller *p2,
	struct gamecube_controller *p3, struct gamecube_controller *p4, bool has_vhsync_interrupt);
void gamecube_tick(struct gamecube *gamecube);
void gamecube_vsync(struct gamecube *gamecube);
void gamecube_hsync(struct gamecube *gamecube);
void gamecube_destroy(struct gamecube **gamecube_ptr);

void gamecube_process_serial_protocol_insert_name_here(struct gamecube *gamecube, uint8_t *data, size_t size);
void gamecube_process_bk2_frame(struct gamecube *gamecube, uint8_t *data, size_t size);
void gamecube_process_dtm_frame(struct gamecube *gamecube, uint8_t *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __GC_H */