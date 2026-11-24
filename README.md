# ring-buffer-c

![CI](https://github.com/mervesulltan/ring-buffer-c/actions/workflows/ci.yml/badge.svg)

A lightweight, malloc-free ring (circular) buffer library in C, designed for embedded systems such as UART receive buffers.

## Features

- No dynamic memory allocation: storage is provided by the caller
- Simple FIFO API with explicit status codes
- NULL-pointer checks on every function
- Unit tests covering empty, full and wrap-around cases
- Builds cleanly with -Wall -Wextra -Wpedantic -std=c11

## Project structure

- include/ring_buffer.h : public API
- src/ring_buffer.c : implementation
- tests/test_ring_buffer.c : unit tests
- Makefile : build and test targets

## Usage

    #include "ring_buffer.h"

    uint8_t storage[64];
    ring_buffer_t rb;

    rb_init(&rb, storage, sizeof(storage));
    rb_push(&rb, 0x41);

    uint8_t byte;
    if (rb_pop(&rb, &byte) == RB_OK) {
        /* byte == 0x41 */
    }

## Build and test

Requires gcc and make (on Windows with MSYS2: mingw32-make).

    make test
    make clean

## API

| Function | Description |
|---|---|
| rb_init | Initialize a buffer with user-provided storage |
| rb_push | Add one byte, returns RB_ERR_FULL if no space |
| rb_pop | Remove oldest byte, returns RB_ERR_EMPTY if none |
| rb_is_empty / rb_is_full | State queries |
| rb_count | Number of stored bytes |

## Design notes

- A separate count field is kept so that the full and empty states can be told apart without wasting a slot.
- When the buffer is full, rb_push rejects new data instead of overwriting old data.
- The library is not interrupt-safe yet. Using it between an ISR and the main loop needs extra care (a possible future improvement).

## License

MIT