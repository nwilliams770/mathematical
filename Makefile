# Compiler
CC = g++
# Compile flags, -Wall gives warnings
CFLAGS = -std=c++17 -Wall
# Linker flags
LDFLAGS = -lSDL2 -pthread

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TESTDIR = tests
GTEST_DIR = /usr/local/opt/googletest

# Find all subdirectories in INCDIR
INCLUDE_DIRS = $(shell find $(INCDIR) -type d -exec echo -I{} \;)
INCLUDE_DIRS += -I$(GTEST_DIR)/include

# Gather all .cpp files in SRCDIR and its subdirectories except main.cpp
SOURCES = $(shell find $(SRCDIR) -name '*.cpp' ! -name 'main.cpp')
MAIN_SOURCE = $(SRCDIR)/main.cpp
# Generate object file names in OBJDIR mirroring the source structure
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
MAIN_OBJECT = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(MAIN_SOURCE))
EXECUTABLE = $(BINDIR)/mathematical

# Gather all .cpp files in TESTDIR and its subdirectories
TEST_SOURCES = $(shell find $(TESTDIR) -name '*.cpp')
# Generate object file names in OBJDIR mirroring the source structure
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SOURCES))
TEST_EXECUTABLE = $(BINDIR)/test_runner

CFLAGS_PROD = $(CFLAGS) -DNDEBUG
CFLAGS_CURRENT = $(CFLAGS)

all: $(EXECUTABLE) $(TEST_EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MAIN_OBJECT)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS_CURRENT) $(INCLUDE_DIRS) -o $@ $^ $(LDFLAGS)

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS_CURRENT) $(INCLUDE_DIRS) -o $@ $^ $(LDFLAGS) -lgtest -lgtest_main

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_CURRENT) $(INCLUDE_DIRS) -c -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_CURRENT) $(INCLUDE_DIRS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)

debug: CFLAGS_CURRENT = $(CFLAGS)
debug: $(EXECUTABLE)

release: CFLAGS_CURRENT = $(CFLAGS_PROD)
release: $(EXECUTABLE)

# TODO FIX
test: $(TEST_EXECUTABLE)
	@mkdir -p $(BINDIR)
	cd $(BINDIR) && ./test_runner > test_results.txt 2>&1
	@echo "Test results written to $(BINDIR)/test_results.txt"