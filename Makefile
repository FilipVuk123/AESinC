CFLAGS   := -Isrc/include  -g # -O3 -ffast-math -Wall -Wextra -pipe -pedantic

SRC_DIR  := src
BIN_DIR  := bin
OBJ_DIR  := $(BIN_DIR)/obj
EXPORT_DIR := export

EXECUTABLE := $(BIN_DIR)/my_program
SRC      := $(wildcard $(SRC_DIR)/*.c)
OBJ      := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


.PHONY: all

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(EXPORT_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -r bin/*
