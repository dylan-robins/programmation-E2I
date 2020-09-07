BIN_DIR := ./bin
SRCS := $(wildcard *.c)
PROGS := $(patsubst %.c,$(BIN_DIR)/%,$(SRCS))
CC := gcc
COPTS := -std=c11 -Wall

# Create the binary subdirectory if it doesn't exist, then build all programs
all: $(BIN_DIR) $(PROGS)

$(BIN_DIR)/%: %.c $(BIN_DIR)
	$(CC) $< -o $@ $(COPTS)

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm -r $(BIN_DIR)

.PHONY: all clean