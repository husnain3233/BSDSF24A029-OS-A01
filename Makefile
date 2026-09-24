# =========================================================
# Top-level Makefile
# Delegates compilation to src/Makefile (recursive make),
# and adds install/uninstall targets for the program + man pages
# =========================================================

SRC_DIR        := src
BIN_DIR        := bin
LIB_DIR        := lib
MAN_DIR        := man

TARGET_STATIC  := $(BIN_DIR)/client_static
TARGET_DYNAMIC := $(BIN_DIR)/client_dynamic

# Installed under PREFIX; DESTDIR lets packagers stage installs elsewhere
PREFIX  := /usr/local
DESTDIR :=

BINDIR  := $(DESTDIR)$(PREFIX)/bin
MANDIR  := $(DESTDIR)$(PREFIX)/share/man

MAN1_PAGES := $(wildcard $(MAN_DIR)/man1/*.1)
MAN3_PAGES := $(wildcard $(MAN_DIR)/man3/*.3)

.PHONY: all clean run-static run-dynamic install uninstall

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

# Installs the (self-contained, statically linked) executable as
# "client", plus the section-1 and section-3 man pages, then
# refreshes the man page index so `man client` works immediately.
install: all
	install -d $(BINDIR)
	install -m 755 $(TARGET_STATIC) $(BINDIR)/client
	install -d $(MANDIR)/man1
	install -m 644 $(MAN1_PAGES) $(MANDIR)/man1/
	install -d $(MANDIR)/man3
	install -m 644 $(MAN3_PAGES) $(MANDIR)/man3/
	-mandb >/dev/null 2>&1 || true
	@echo "Installed 'client' to $(BINDIR)"
	@echo "Installed man pages to $(MANDIR)"

uninstall:
	rm -f $(BINDIR)/client
	rm -f $(addprefix $(MANDIR)/man1/,$(notdir $(MAN1_PAGES)))
	rm -f $(addprefix $(MANDIR)/man3/,$(notdir $(MAN3_PAGES)))
	-mandb >/dev/null 2>&1 || true
