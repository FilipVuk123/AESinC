CFLAGS    := -g -O3 -ffast-math -Wall -Wextra -pipe -pedantic -std=gnu99
IFLAGS	  := -Isrc/include 

SRC_DIR   := src
BIN_DIR   := bin
OBJ_DIR   := $(BIN_DIR)/obj
EXPORT_DIR:= export
LIB_DIR   := $(EXPORT_DIR)/lib

LIBRARY   := $(LIB_DIR)/libaes.a
SRC       := $(wildcard $(SRC_DIR)/*.c)
OBJ       := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

.PHONY: all clean

all: $(LIBRARY)

$(LIBRARY): $(OBJ) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(EXPORT_DIR) $(LIB_DIR):
	mkdir -p $@

clean:
	rm -r $(BIN_DIR)/*
	rm -r $(LIB_DIR)/*