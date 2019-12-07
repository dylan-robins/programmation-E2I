BIN_DIR := ./bin
SRCS := $(wildcard *.c)
PROGS := $(patsubst %.c,$(BIN_DIR)/%,$(SRCS))

# Create the binary subdirectory if it doesn't exist, then build all programs
all: $(BIN_DIR) $(PROGS)

$(BIN_DIR)/%: %.c $(BIN_DIR)
	gcc $< -o $@ -std=c11 -Wall -lm

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm -r $(BIN_DIR)

.PHONY: all clean