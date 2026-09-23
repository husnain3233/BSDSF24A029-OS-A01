# =========================================================
# src/Makefile (Feature-4: Static + Dynamic Library Build)
#
# Builds BOTH libmyutils.a (static) and libmyutils.so (dynamic)
# from the utility source files, then produces two executables:
#   client_static  -> linked directly against libmyutils.a
#   client_dynamic -> linked against libmyutils.so
# =========================================================

CC        := gcc
CFLAGS    := -Wall -I../include -fPIC
AR        := ar
ARFLAGS   := rcs
RANLIB    := ranlib

OBJ_DIR   := ../obj
LIB_DIR   := ../lib
BIN_DIR   := ../bin

STATIC_LIB   := $(LIB_DIR)/libmyutils.a
DYNAMIC_LIB  := $(LIB_DIR)/libmyutils.so

TARGET_STATIC  := $(BIN_DIR)/client_static
TARGET_DYNAMIC := $(BIN_DIR)/client_dynamic

# Utility source/object files that go INTO both libraries
LIB_SOURCES := mystrfunctions.c myfilefunctions.c
LIB_OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SOURCES))

# The driver source/object that links AGAINST the libraries
MAIN_SOURCE := main.c
MAIN_OBJECT := $(OBJ_DIR)/main.o

.PHONY: all clean static dynamic

all: static dynamic

static: $(TARGET_STATIC)
dynamic: $(TARGET_DYNAMIC)

# --- Static executable: link main.o directly against the .a file ---
# (linking the .a file by path, not with -l, avoids any ambiguity
#  with the .so of the same name also sitting in lib/)
$(TARGET_STATIC): $(MAIN_OBJECT) $(STATIC_LIB)
	$(CC) $(MAIN_OBJECT) $(STATIC_LIB) -o $(TARGET_STATIC)

# --- Dynamic executable: link main.o against the .so via -l ---
$(TARGET_DYNAMIC): $(MAIN_OBJECT) $(DYNAMIC_LIB)
	$(CC) $(MAIN_OBJECT) -L$(LIB_DIR) -lmyutils -o $(TARGET_DYNAMIC)

# --- Build the static archive ---
$(STATIC_LIB): $(LIB_OBJECTS)
	$(AR) $(ARFLAGS) $(STATIC_LIB) $(LIB_OBJECTS)
	$(RANLIB) $(STATIC_LIB)

# --- Build the shared object ---
$(DYNAMIC_LIB): $(LIB_OBJECTS)
	$(CC) -shared -o $(DYNAMIC_LIB) $(LIB_OBJECTS)

# --- Compile every .c into position-independent obj/%.o ---
# (-fPIC applies to all objects here; it's required for the .so
#  and is harmless for objects also used in the .a)
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(STATIC_LIB) $(DYNAMIC_LIB) $(TARGET_STATIC) $(TARGET_DYNAMIC)
