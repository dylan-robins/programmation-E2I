BIN_DIR := ./bin
SRCS := my_file my_cp id3Edit
PROGS := $(patsubst %, $(BIN_DIR)/%, $(SRCS))

# Create the binary subdirectory if it doesn't exist, then build all programs
all: $(BIN_DIR) $(PROGS)

$(BIN_DIR)/my_file: my_file.o recognition.o
	gcc $^ -o $@

$(BIN_DIR)/my_cp: my_cp.o
	gcc $^ -o $@

$(BIN_DIR)/id3Edit: id3Edit.o
	gcc $^ -o $@

%.o: %.c
	gcc $< -o $@ -c -std=c11 -Wall -lm -g

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm -r $(BIN_DIR) *.o

.PHONY: all clean