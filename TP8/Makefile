BIN_DIR := ./bin
OBJ_DIR := ./obj
TEST_DIR := ./tests

SRCS := my_file my_cp my_wc id3Edit
PROGS := $(patsubst %, $(BIN_DIR)/%, $(SRCS))

# Create the binary subdirectory if it doesn't exist, then build all programs
all: $(BIN_DIR) $(OBJ_DIR) $(PROGS) tests
	@echo "##### Compilation completed, tests passed"

$(BIN_DIR)/my_file: $(patsubst %, $(OBJ_DIR)/%, my_file.o recognition.o)
	@echo "##### COMPILING MY_FILE"
	gcc $^ -o $@

$(BIN_DIR)/my_cp: $(patsubst %, $(OBJ_DIR)/%, my_cp.o)
	@echo "##### COMPILING MY_CP"
	gcc $^ -o $@

$(BIN_DIR)/id3Edit: $(patsubst %, $(OBJ_DIR)/%, id3Edit.o)
	@echo "##### COMPILING ID3EDIT"
	gcc $^ -o $@

$(BIN_DIR)/my_wc: $(patsubst %, $(OBJ_DIR)/%, my_wc.o)
	@echo "##### COMPILING MY_WC"
	gcc $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@echo "##### COMPILING $@"
	gcc $< -o $@ -c -std=c11 -Wall -lm -g -pedantic

$(BIN_DIR):
	mkdir $(BIN_DIR)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	@echo "##### CLEANING FILES"
	rm -r $(BIN_DIR) $(OBJ_DIR)

tests:
	@echo "##### RUNNING TESTS"
	for script in $(TEST_DIR)/*.sh; do bash $$script; done


.PHONY: all clean tests $(TEST_FILES)