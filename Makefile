CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

SRC     = src/ring_buffer.c
TEST    = tests/test_ring_buffer.c
BUILD   = build
TARGET  = $(BUILD)/test_ring_buffer.exe

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SRC) $(TEST) include/ring_buffer.h | $(BUILD)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET)

$(BUILD):
	mkdir $(BUILD)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD)