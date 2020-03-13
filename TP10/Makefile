BIN_DIR := ./bin
OBJ_DIR := ./obj

SRCS := sort_test sort_efficiency
PROGS := $(patsubst %, $(BIN_DIR)/%, $(SRCS))

all: $(OBJ_DIR) $(BIN_DIR) $(PROGS)


$(OBJ_DIR)/%.o: %.c
	@echo "##### COMPILING $@"
	gcc $< -o $@ -c -pg -O3 -std=c11 -Wall -lm -g -pedantic

$(BIN_DIR)/sort_test: $(patsubst %, $(OBJ_DIR)/%, sort_test.o sort.o)
	@echo "##### COMPILING SORT"
	gcc $^ -o $@

$(BIN_DIR)/sort_efficiency: $(patsubst %, $(OBJ_DIR)/%, sort.o sort_efficiency.o)
	@echo "##### COMPILING SORT_EFFICIENCY"
	gcc $^ -lm -o $@ -pg

$(BIN_DIR):
	mkdir $(BIN_DIR)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	@echo "##### CLEANING FILES"
	@rm -r $(BIN_DIR) $(OBJ_DIR)


.PHONY: all clean