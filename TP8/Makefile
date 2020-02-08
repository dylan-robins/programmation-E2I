BIN_DIR := ./bin
OBJ_DIR := ./obj
SRCS := my_file my_cp my_wc id3Edit
PROGS := $(patsubst %, $(BIN_DIR)/%, $(SRCS))

# Create the binary subdirectory if it doesn't exist, then build all programs
all: $(BIN_DIR) $(OBJ_DIR) $(PROGS)

$(BIN_DIR)/my_file: $(patsubst %, $(OBJ_DIR)/%, my_file.o recognition.o)
	gcc $^ -o $@

$(BIN_DIR)/my_cp: $(patsubst %, $(OBJ_DIR)/%, my_cp.o)
	gcc $^ -o $@

$(BIN_DIR)/id3Edit: $(patsubst %, $(OBJ_DIR)/%, id3Edit.o)
	gcc $^ -o $@

$(BIN_DIR)/my_wc: $(patsubst %, $(OBJ_DIR)/%, my_wc.o)
	gcc $^ -o $@

$(OBJ_DIR)/%.o: %.c
	gcc $< -o $@ -c -std=c11 -Wall -lm -g -pedantic

$(BIN_DIR):
	mkdir $(BIN_DIR)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -r $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean