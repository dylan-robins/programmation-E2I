BUILD_DIR := ./build
OBJ_DIR   := $(BUILD_DIR)/obj

all: $(BUILD_DIR) $(OBJ_DIR) $(BUILD_DIR)/MakefileGenerator

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR)/MakefileGenerator: $(OBJ_DIR)/MakefileGenerator.o $(OBJ_DIR)/stringArray.o $(OBJ_DIR)/strUtils.o
	gcc -o $@ $^

$(OBJ_DIR)/%.o: %.c
	gcc -c -Wall -pedantic -o $@ $<

clean:
	rm -rf $(BUILD_DIR)


.PHONY: all clean