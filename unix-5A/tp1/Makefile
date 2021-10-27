CC := gcc
CFLAGS := -Wall -pedantic -std=c11
BUILD_DIR := ./build
OBJ_DIR := $(BUILD_DIR)/obj

PROGS := listeAttributs processFichier

all: $(BUILD_DIR) $(OBJ_DIR) $(PROGS:%=$(BUILD_DIR)/%)

listeAttributs_objs := printInodeStats.o listeAttributs.o
$(BUILD_DIR)/listeAttributs: $(listeAttributs_objs:%=$(OBJ_DIR)/%)
	$(CC) $(CFLAGS) $^ -o $@

processFichier_objs := processFichier.o
$(BUILD_DIR)/processFichier: $(processFichier_objs:%=$(OBJ_DIR)/%)
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