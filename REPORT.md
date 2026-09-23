
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
