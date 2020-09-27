BIN_DIR := ./bin
OBJ_DIR := ./obj

all: $(BIN_DIR) $(OBJ_DIR) $(BIN_DIR)/test

# apres l'etiquete (test:) un .o pour chaque .cpp compilé
# cette ligne genere un executable appele 'test'
$(BIN_DIR)/test: $(OBJ_DIR)/main.o $(OBJ_DIR)/pile.o $(OBJ_DIR)/vec3d.o $(OBJ_DIR)/point.o
	g++ -Wall -o $@ $^

# cette ligne compile tous les .ccp et genere des .o avec le meme nom
$(OBJ_DIR)/%.o: %.cpp
	g++ -c -o $@ $< -lm

# cette ligne compile tous les pairs .ccp/.h et genere des .o avec le meme nom
$(OBJ_DIR)/%.o: %.cpp %.h
	g++ -c -o $@ $< -lm

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) test

.PHONY: clean