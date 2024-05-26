# Compiler
CC = g++
# Compile flags, -Wall gives warnings
CFLAGS = -std=c++11 -Wall
# Linker flags
LDFLAGS = -lncurses

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Find all subdirectories in INCDIR
INCLUDE_DIRS = $(shell find $(INCDIR) -type d -exec echo -I{} \;)

# Gather all .cpp files in SRCDIR and its subdirectories
SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
# Generate object file names in OBJDIR mirroring the source structure
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/mathematical

CFLAGS_PROD = $(CFLAGS) -DNDEBUG
CFLAGS_CURRENT = $(CFLAGS)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS_CURRENT) $(INCLUDE_DIRS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_CURRENT) $(INCLUDE_DIRS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)

debug: CFLAGS_CURRENT = $(CFLAGS)
debug: $(EXECUTABLE)

release: CFLAGS_CURRENT = $(CFLAGS_PROD)
release: $(EXECUTABLE)