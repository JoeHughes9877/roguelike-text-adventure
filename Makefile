# Compiler to use
CC = gcc

# Compiler flags
# -Wall: Enable all standard warnings
# -Wextra: Enable extra warnings
# -std=c11: Use C11 standard
# -pedantic: Enforce strict adherence to the C standard
# -Iinclude: Add the 'include' directory to the search path for header files
# -D_GNU_SOURCE: Define _GNU_SOURCE to enable GNU extensions like strndup
CFLAGS = -Wall -Wextra -std=c11 -pedantic -Iinclude -D_GNU_SOURCE

# Linker flags for libraries
# -lsqlite3: Link against the SQLite3 library
LDFLAGS = -lsqlite3

# Directory for source files
SRCDIR = src

# Directory for object files (will be created if it doesn't exist)
OBJDIR = obj

# Name of the executable
TARGET = game

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# List of object files, derived from source files
# Replaces 'src/' with 'obj/' and '.c' with '.o'
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Default target: builds the executable
all: $(TARGET)

# Target to create the object directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Rule to link the object files into the executable
$(TARGET): $(OBJS) | $(OBJDIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Rule to compile each C source file into an object file
# $<: The first prerequisite (the .c file)
# $@: The target (the .o file)
# -c: Compile only, do not link
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets: targets that do not correspond to actual files
.PHONY: all clean

# Target to clean up compiled files and the object directory
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET)
	@rm -rf $(OBJDIR)
	@echo "Clean complete."

# Dependencies: automatically generate dependencies for header files
# This ensures that if a header file changes, the relevant source files are recompiled.
# You might need to run 'make depend' once or include this in your 'all' target if you're not using
# a more advanced dependency generation system. For simplicity, this Makefile assumes you'll
# manually re-run `make` if headers change, or you can add a rule for auto-dependency generation.
# For this project, given the simple structure, the above rules should suffice for most changes.
