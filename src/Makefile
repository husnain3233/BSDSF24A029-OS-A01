# =========================================================
# src/Makefile (Feature-3: Static Library Build)
#
# Builds libmyutils.a from the utility source files, then
# links main.o against that library to produce client_static
# =========================================================

CC        := gcc
CFLAGS    := -Wall -I../include
AR        := ar
ARFLAGS   := rcs
RANLIB    := ranlib

OBJ_DIR   := ../obj
LIB_DIR   := ../lib
BIN_DIR   := ../bin

LIBRARY   := $(LIB_DIR)/libmyutils.a
TARGET    := $(BIN_DIR)/client_static

# Utility source/object files that go INTO the static library
LIB_SOURCES := mystrfunctions.c myfilefunctions.c
LIB_OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SOURCES))

# The driver source/object that links AGAINST the library
MAIN_SOURCE := main.c
MAIN_OBJECT := $(OBJ_DIR)/main.o

.PHONY: all clean

all: $(TARGET)

# Link the final executable against the static library
$(TARGET): $(MAIN_OBJECT) $(LIBRARY)
	$(CC) $(MAIN_OBJECT) -L$(LIB_DIR) -lmyutils -o $(TARGET)

# Archive the utility object files into the static library
$(LIBRARY): $(LIB_OBJECTS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(LIB_OBJECTS)
	$(RANLIB) $(LIBRARY)

# Generic pattern rule: compile any .c into obj/%.o
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(LIBRARY) $(TARGET)
