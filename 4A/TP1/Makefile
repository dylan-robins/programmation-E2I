BIN_DIR := ./bin
SRCS := $(wildcard *.cpp)
PROGS := $(patsubst %.cpp,$(BIN_DIR)/%,$(SRCS))

# Create the binary subdirectory if it doesn't exist, then build all programs
all: $(BIN_DIR) $(PROGS)

$(BIN_DIR)/%: %.cpp $(BIN_DIR)
	g++ $< -o $@ -Wall -g

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm -r $(BIN_DIR)

.PHONY: clean