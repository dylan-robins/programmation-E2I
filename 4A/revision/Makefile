BIN_DIR := ./bin
OBJ_DIR := ./obj

OBJS := $(patsubst %, $(OBJ_DIR)/%.o, fichiers)

all: $(BIN_DIR) $(OBJ_DIR) $(BIN_DIR)/main

# apres l'etiquete (main:) un .o pour chaque .cpp compilé
# cette ligne genere un executable appele 'main'
$(BIN_DIR)/main: $(OBJS)
	g++ -Wall -o $@ $^ -g

# cette ligne compile tous les .ccp et genere des .o avec le meme nom
$(OBJ_DIR)/%.o: %.cpp
	g++ -c -o $@ $< -lm -g

# cette ligne compile tous les pairs .ccp/.h et genere des .o avec le meme nom
$(OBJ_DIR)/%.o: %.cpp %.h
	g++ -c -o $@ $< -lm -g

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

tar: clean
	tar cvzf TP.tgz ./*

.PHONY: clean