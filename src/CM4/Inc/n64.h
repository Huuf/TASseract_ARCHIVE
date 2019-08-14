#ifndef __N64_H
#define __N64_H

#ifdef __cplusplus
extern "C" {
#endif

struct n64;

void n64_setup(struct n64 **n64_ptr, struct n64_controller *p1, struct n64_controller *p2,
	struct n64_controller *p3, struct n64_controller *p4, bool has_vhsync_interrupt);
void n64_tick(struct n64 *n64);
void n64_vsync(struct n64 *n64);
void n64_hsync(struct n64 *n64);
void n64_destroy(struct n64 **n64_ptr);

void n64_process_serial_protocol_insert_name_here(struct n64 *n64, uint8_t *data, size_t size);
void n64_process_bk2_frame(struct n64 *n64, uint8_t *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __N64_H */
