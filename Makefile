# == Meowstuck Makefile ==

# C++ flags
CXX := clang++
CXXFLAGS := -std=c++14 -O2 -g -Wall -pedantic
LIBS := -lsfml-system -lsfml-window -lsfml-graphics
INCLUDES := -Iinclude/

# Project directories
SRCDIR := src
BUILDDIR := build
BINDIR := bin

# Target variables
TARGETNAME := meowstuck
TARGET := $(BINDIR)/$(TARGETNAME)
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
CLEANDELETE :=

HEADERS := $(shell find $(SRCDIR) -type f -name *.h)
SOURCEDEPS := $(HEADERS)

# MAKE TARGETS
# ------------

# Default 'all' target
all: $(TARGETNAME)

$(TARGETNAME): $(TARGET)

# Object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@#echo '$(CXX) -c $$(CXXFLAGS) $$(INCLUDES) -o $@ $<'
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -o $@ $<

# App target
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@#echo '$(CXX) $$(LIBS) -o $(TARGET) $(OBJECTS)'
	$(CXX) $(LIBS) -o $(TARGET) $(OBJECTS)

# Clean generated files
clean:
	rm -r $(BUILDDIR)
	rm -f $(TARGET) $(CLEANDELETE)

run: $(TARGET)
	@echo Running $(TARGET) ...
	@$(TARGET)

echoflags:
	@echo 'CXXFLAGS := $(CXXFLAGS)'
	@echo
	@echo 'LIBS := $(LIBS)'
	@echo
	@echo 'INCLUDES := $(INCLUDES)'
	@echo

.PHONY: all $(TARGETNAME) clean run echoflags
