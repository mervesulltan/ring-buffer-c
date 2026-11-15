#include "ring_buffer.h"

rb_status_t rb_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity)
{
    if (rb == NULL || storage == NULL || capacity == 0) {
        return RB_ERR_NULL;
    }

    rb->buffer   = storage;
    rb->capacity = capacity;
    rb->head     = 0;
    rb->tail     = 0;
    rb->count    = 0;

    return RB_OK;
}

rb_status_t rb_push(ring_buffer_t *rb, uint8_t byte)
{
    if (rb == NULL) {
        return RB_ERR_NULL;
    }
    if (rb->count == rb->capacity) {
        return RB_ERR_FULL;
    }

    rb->buffer[rb->head] = byte;
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count++;

    return RB_OK;
}

rb_status_t rb_pop(ring_buffer_t *rb, uint8_t *byte)
{
    if (rb == NULL || byte == NULL) {
        return RB_ERR_NULL;
    }
    if (rb->count == 0) {
        return RB_ERR_EMPTY;
    }

    *byte = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count--;

    return RB_OK;
}

bool rb_is_empty(const ring_buffer_t *rb)
{
    return (rb == NULL) || (rb->count == 0);
}

bool rb_is_full(const ring_buffer_t *rb)
{
    return (rb != NULL) && (rb->count == rb->capacity);
}

size_t rb_count(const ring_buffer_t *rb)
{
    return (rb == NULL) ? 0 : rb->count;
}