CC := gcc
CFLAGS := -Wall -pedantic -std=c11
BUILD_DIR := ./bin
OBJ_DIR := $(BUILD_DIR)/obj

PROGS := test_fork test_exec

all: $(BUILD_DIR) $(OBJ_DIR) $(PROGS:%=$(BUILD_DIR)/%)

test_fork_objs := test_fork.o
$(BUILD_DIR)/test_fork: $(test_fork_objs:%=$(OBJ_DIR)/%)
	$(CC) $(CFLAGS) $^ -o $@

test_exec_objs := test_exec.o
$(BUILD_DIR)/test_exec: $(test_exec_objs:%=$(OBJ_DIR)/%)
	$(CC) $(CFLAGS) $^ -o $@

# cette ligne compile tous les .c et genere des .o avec le meme nom
$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR)

tar: clean
	tar cvzf TP_ROBINS.tgz ./*

.PHONY: clean