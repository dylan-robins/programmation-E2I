BUILD_DIR := ./build
OBJ_DIR   := $(BUILD_DIR)/obj

all: $(BUILD_DIR) $(OBJ_DIR) $(BUILD_DIR)/snake

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR)/snake: $(OBJ_DIR)/main.o $(OBJ_DIR)/ttyGraphics.o $(OBJ_DIR)/map.o $(OBJ_DIR)/snake.o
	gcc -o $@ $^

$(OBJ_DIR)/%.o: %.c
	gcc -g -c -Wall -pedantic -o $@ $<

clean:
	rm -rf $(BUILD_DIR)


.PHONY: all clean