#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer.h"

static int tests_run = 0;

#define CHECK(cond)                                                    \
    do {                                                               \
        tests_run++;                                                   \
        if (!(cond)) {                                                 \
            printf("FAIL: %s (line %d)\n", #cond, __LINE__);           \
            exit(1);                                                   \
        }                                                              \
    } while (0)

static void test_init(void)
{
    uint8_t storage[4];
    ring_buffer_t rb;

    CHECK(rb_init(&rb, storage, 4) == RB_OK);
    CHECK(rb_is_empty(&rb));
    CHECK(!rb_is_full(&rb));
    CHECK(rb_count(&rb) == 0);

    CHECK(rb_init(NULL, storage, 4) == RB_ERR_NULL);
    CHECK(rb_init(&rb, NULL, 4) == RB_ERR_NULL);
    CHECK(rb_init(&rb, storage, 0) == RB_ERR_NULL);
}

static void test_push_pop(void)
{
    uint8_t storage[4];
    ring_buffer_t rb;
    uint8_t out = 0;

    rb_init(&rb, storage, 4);

    CHECK(rb_push(&rb, 10) == RB_OK);
    CHECK(rb_push(&rb, 20) == RB_OK);
    CHECK(rb_count(&rb) == 2);

    CHECK(rb_pop(&rb, &out) == RB_OK);
    CHECK(out == 10);                 /* FIFO: first in, first out */
    CHECK(rb_pop(&rb, &out) == RB_OK);
    CHECK(out == 20);
    CHECK(rb_is_empty(&rb));
}

static void test_empty_and_full(void)
{
    uint8_t storage[2];
    ring_buffer_t rb;
    uint8_t out = 0;

    rb_init(&rb, storage, 2);

    CHECK(rb_pop(&rb, &out) == RB_ERR_EMPTY);

    CHECK(rb_push(&rb, 1) == RB_OK);
    CHECK(rb_push(&rb, 2) == RB_OK);
    CHECK(rb_is_full(&rb));
    CHECK(rb_push(&rb, 3) == RB_ERR_FULL);  /* old data must not be overwritten */

    CHECK(rb_pop(&rb, &out) == RB_OK);
    CHECK(out == 1);
}

static void test_wrap_around(void)
{
    uint8_t storage[3];
    ring_buffer_t rb;
    uint8_t out = 0;

    rb_init(&rb, storage, 3);

    /* fill, drain two, then push past the end of the array */
    rb_push(&rb, 1);
    rb_push(&rb, 2);
    rb_push(&rb, 3);
    rb_pop(&rb, &out);
    rb_pop(&rb, &out);

    CHECK(rb_push(&rb, 4) == RB_OK);   /* head wraps to index 0 */
    CHECK(rb_push(&rb, 5) == RB_OK);
    CHECK(rb_is_full(&rb));

    CHECK(rb_pop(&rb, &out) == RB_OK);
    CHECK(out == 3);
    CHECK(rb_pop(&rb, &out) == RB_OK);
    CHECK(out == 4);
    CHECK(rb_pop(&rb, &out) == RB_OK);
    CHECK(out == 5);
    CHECK(rb_is_empty(&rb));
}

int main(void)
{
    test_init();
    test_push_pop();
    test_empty_and_full();
    test_wrap_around();

    printf("All tests passed (%d checks)\n", tests_run);
    return 0;
}