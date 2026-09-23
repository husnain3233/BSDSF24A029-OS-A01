# =========================================================
# src/Makefile
# Compiles all .c files in this directory into object files
# under ../obj, then links them into ../bin/client
# =========================================================

CC       := gcc
CFLAGS   := -Wall -I../include
OBJ_DIR  := ../obj
BIN_DIR  := ../bin
TARGET   := $(BIN_DIR)/client

SOURCES  := $(wildcard *.c)
OBJECTS  := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
