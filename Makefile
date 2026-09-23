# =========================================================
# Top-level Makefile
# Delegates the actual compilation to src/Makefile
# (recursive make approach)
# =========================================================

SRC_DIR := src
BIN_DIR := bin
TARGET  := $(BIN_DIR)/client_static

.PHONY: all clean run

all:
	$(MAKE) -C $(SRC_DIR)

clean:
	$(MAKE) -C $(SRC_DIR) clean

run: all
	./$(TARGET)
