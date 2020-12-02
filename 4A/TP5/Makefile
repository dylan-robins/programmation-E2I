BIN_DIR := ./bin
OBJ_DIR := ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%.o, main points)

all: $(BIN_DIR) $(OBJ_DIR) $(BIN_DIR)/test

# apres l'etiquete (test:) un .o pour chaque .cpp compilé
# cette ligne genere un executable appele 'test'
$(BIN_DIR)/test: $(OBJS)
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
	rm -rf $(BIN_DIR) $(OBJ_DIR) test

tar: clean
	tar cvzf TP_ROBINS.tgz ./*

.PHONY: clean