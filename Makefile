# =========================================================
# Top-level Makefile
# Delegates the actual compilation to src/Makefile
# (recursive make approach)
# =========================================================

SRC_DIR        := src
BIN_DIR        := bin
LIB_DIR        := lib
TARGET_STATIC  := $(BIN_DIR)/client_static
TARGET_DYNAMIC := $(BIN_DIR)/client_dynamic

.PHONY: all clean run-static run-dynamic

all:
	$(MAKE) -C $(SRC_DIR)

clean:
	$(MAKE) -C $(SRC_DIR) clean

run-static: all
	./$(TARGET_STATIC)

# Sets LD_LIBRARY_PATH just for this command so the dynamic
# loader can find lib/libmyutils.so
run-dynamic: all
	LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH ./$(TARGET_DYNAMIC)
