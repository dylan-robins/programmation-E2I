BIN_DIR := ./bin
OBJ_DIR := ./obj

OBJS := $(patsubst %, $(OBJ_DIR)/%.o, main complexe matrice)

all: $(BIN_DIR) $(OBJ_DIR) $(BIN_DIR)/test

$(BIN_DIR)/test: $(OBJS)
	g++ -Wall -o $@ $^ -g

$(OBJ_DIR)/%.o: %.cpp
	g++ -c -o $@ $< -lm -g

$(OBJ_DIR)/%.o: %.cpp %.h
	g++ -c -o $@ $< -lm -g

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

tar: clean
	tar cvzf exam_robins_dylan.tgz ./*

.PHONY: clean