BIN_DIR := ./bin
OBJ_DIR := ./obj
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default: compile main program
all: dirs $(BIN_DIR)/main

# main program linking rule: first make the bin directory, then link
$(BIN_DIR)/main: $(OBJS)
	echo $(OBJS)
	gcc $(OBJS) -o $@

# object file compilation
$(OBJ_DIR)/%.o: %.c
	gcc -c $< -o $@ -std=c11 -Wall -g

dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	rm -r $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean dirs