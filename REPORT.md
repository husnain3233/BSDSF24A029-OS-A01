
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

## Feature-4: Creating and using a Dynamic Library

### Q1: What is -fPIC and why is it required for shared libraries?
-fPIC (Position-Independent Code) tells the compiler to generate machine code that does not
depend on being loaded at a fixed memory address. This matters because a shared library (.so)
can be loaded into different memory addresses in different processes, or even at different
addresses within the same process depending on what else is loaded. Without -fPIC, the code
would use absolute memory addresses baked in at compile time, which only works if the code is
guaranteed to live at one specific address — true for a normal executable, but not for a
library that many different programs load independently. PIC code instead uses relative
addressing so it works correctly no matter where in memory it ends up.

### Q2: Explain the file size difference between client_static and client_dynamic.
client_static is larger because static linking physically copies the compiled machine code of
every function from libmyutils.a directly into the executable at link time, making the binary
fully self-contained. client_dynamic is smaller because it only contains a reference to the
functions it needs — the actual code stays in the external libmyutils.so file, loaded into
memory separately at runtime by the dynamic loader. In this project the size gap is modest
since the utility library itself is small (a handful of string/file functions); the difference
becomes much more dramatic with larger libraries, since the dynamic executable's size stays
roughly constant while the static one grows with every function pulled in from the library.

### Q3: What is LD_LIBRARY_PATH, and what does needing it reveal about the dynamic loader?
LD_LIBRARY_PATH is an environment variable that tells the operating system's dynamic loader
additional directories to search when looking for shared libraries a program depends on. It
was necessary here because libmyutils.so lives in a custom project folder (lib/) rather than
a standard system library location like /usr/lib, so the loader had no way to find it by
default, producing the "cannot open shared object file" error. This demonstrates that with
dynamic linking, resolving library dependencies is deferred from link time to run time: the
executable only stores the library's name, and it becomes the operating system's responsibility,
via the dynamic loader, to locate and load the actual library code into memory before the
program can execute. This is fundamentally different from static linking, where all dependencies
are resolved and embedded once at build time.
