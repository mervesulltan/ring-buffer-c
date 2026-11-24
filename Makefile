CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

SRC     = src/ring_buffer.c
TEST    = tests/test_ring_buffer.c
BUILD   = build
TARGET  = $(BUILD)/test_ring_buffer.exe

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(BUILD) mkdir $(BUILD)
    RMDIR = if exist $(BUILD) rmdir /s /q $(BUILD)
    RUN   = $(BUILD)\test_ring_buffer.exe
else
    MKDIR = mkdir -p $(BUILD)
    RMDIR = rm -rf $(BUILD)
    RUN   = ./$(TARGET)
endif

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SRC) $(TEST) include/ring_buffer.h
	$(MKDIR)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET)

test: $(TARGET)
	$(RUN)

clean:
	$(RMDIR)