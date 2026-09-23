
## Feature-2: Multi-file Project using Make Utility

### Q1: Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from linking against a library?
This rule tells make that `bin/client` depends on all the object files listed in `$(OBJECTS)`.
When any object file is newer than the target (or the target doesn't exist), make re-runs
the recipe, which invokes gcc to link all the .o files directly into a single executable.
This differs from linking against a library (e.g. `gcc main.o -lmylib -L./lib`), where instead
of compiling every source file into the final binary each time, pre-compiled code is bundled
into a .a (static) or .so (shared) library once, and the executable simply links against that
library file. Direct object linking recompiles everything from source; library linking reuses
already-compiled code.

### Q2: What is a git tag and why is it useful? Difference between simple and annotated tags?
A git tag is a fixed, named pointer to a specific commit, typically used to mark release points
(e.g. v1.0). It's useful because it gives a memorable, permanent reference to an exact version
of the codebase, independent of branch history, which is essential for tracking releases.
A simple (lightweight) tag is just a pointer to a commit, with no extra metadata.
An annotated tag is a full object in git's database, storing the tagger's name, email, date,
and a message, similar to a commit. Annotated tags are recommended for public releases because
of this extra metadata and because they can be GPG-signed for verification.

### Q3: What is the purpose of a GitHub "Release"? Why attach binaries?
A GitHub Release packages a specific tagged version of the project into a shareable, user-facing
entry on the repository, including release notes describing what changed. Attaching binaries
(like the compiled bin/client executable) lets users download and run the program directly,
without needing to clone the repository and build it themselves from source. This is especially
useful for end users who just want to use the software rather than develop it.

## Feature-3: Creating and using a Static Library

### Q1: Compare the Feature-2 and Feature-3 Makefiles. Key differences?
The Feature-2 Makefile compiled all .c files into .o files and linked every object file directly
into the final executable in one step. The Feature-3 Makefile splits the sources into two groups:
LIB_SOURCES (mystrfunctions.c, myfilefunctions.c) and MAIN_SOURCE (main.c). It adds new
variables (AR, ARFLAGS, RANLIB, LIBRARY, LIB_DIR) and a new rule that archives the utility
object files into lib/libmyutils.a using "ar rcs" followed by "ranlib". The final link step changed
from linking all .o files together to linking only main.o against the library using
"-L../lib -lmyutils", so the executable (client_static) now depends on the library as an
intermediate build artifact rather than on the raw object files directly.

### Q2: What is the purpose of ar? Why use ranlib right after it?
ar (archiver) bundles multiple compiled object files into a single archive file (a .a static
library), similar to how a zip file bundles multiple files together. This lets many object files
be distributed and linked against as one unit instead of many. ranlib generates or updates an
index (symbol table) stored inside the archive, which lists which symbols are defined in which
object file. This index lets the linker quickly find the right object file for an unresolved
symbol without scanning the whole archive sequentially, which speeds up linking. On many modern
systems "ar rcs" already builds this index automatically, but running ranlib explicitly (or using
the "s" flag, as we did) guarantees it's present and up to date.

### Q3: Are mystrlen's symbols present in client_static via nm? What does this show about static linking?
Yes — running "nm bin/client_static | grep mystrlen" shows "T mystrlen", where the "T" symbol
type means the function's actual code is defined in the text (code) section of the executable
itself. This confirms that static linking physically copies the required object code from the
library (libmyutils.a) into the final executable at link time. Unlike dynamic linking, where a
program merely references a shared library that must be present at runtime, a statically linked
executable is fully self-contained: all the library code it depends on becomes part of the binary,
so it can run without libmyutils.a existing anywhere on the system.
