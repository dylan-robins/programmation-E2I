BIN_DIR := ./bin
OBJ_DIR := ./obj

all: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/dico

COPTS := -g -Wall -pedantic

$(BIN_DIR)/dico: fonctions_prof.o $(OBJ_DIR)/dico.o $(OBJ_DIR)/fonctions.o
	gcc $(COPTS) $^ -o $(BIN_DIR)/dico

$(OBJ_DIR)/%.o: %.c
	gcc $(COPTS) -c $^ -std=c11 -o $@

$(BIN_DIR):
	mkdir $(BIN_DIR)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	
clean:
	@rm -r $(OBJ_DIR) $(BIN_DIR)
	
.PHONY: all clean
