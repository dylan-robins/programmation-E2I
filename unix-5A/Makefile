BUILD_DIR := ./build

SRCS = $(wildcard *.c) # c sources

PROGS := $(patsubst %.c,$(BUILD_DIR)/%,$(SRCS))

CC := gcc

# Create the binary subdirectory if it doesn't exist, then build all programs
all: $(BUILD_DIR) $(PROGS)

$(BUILD_DIR)/%: %.c $(BUILD_DIR)
	$(CC) $< -o $@ -Wall -g

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm -r $(BUILD_DIR)

.PHONY: all clean