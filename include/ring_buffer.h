#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Return codes for ring buffer operations */
typedef enum {
    RB_OK = 0,
    RB_ERR_NULL,   /* a NULL pointer was passed */
    RB_ERR_FULL,   /* no space left to push */
    RB_ERR_EMPTY   /* nothing to pop */
} rb_status_t;

/* Ring buffer state. Do not modify the fields directly. */
typedef struct {
    uint8_t *buffer;   /* user-provided storage */
    size_t   capacity; /* total number of slots */
    size_t   head;     /* next write position */
    size_t   tail;     /* next read position */
    size_t   count;    /* number of stored elements */
} ring_buffer_t;

rb_status_t rb_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity);
rb_status_t rb_push(ring_buffer_t *rb, uint8_t byte);
rb_status_t rb_pop(ring_buffer_t *rb, uint8_t *byte);

bool   rb_is_empty(const ring_buffer_t *rb);
bool   rb_is_full(const ring_buffer_t *rb);
size_t rb_count(const ring_buffer_t *rb);

#endif /* RING_BUFFER_H */