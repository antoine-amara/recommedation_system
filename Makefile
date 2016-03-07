TARGET   = recommender_system

CC       = g++
# compiling flags here
CFLAGS   = -std=c++11 -Wall -Iinclude/

LINKER   = g++ -o
# linking flags here
LFLAGS   = -Wall -lm -lgsl -lgslcblas -Iinclude/

# change these to set the proper directories where each files shoould be
SRCDIR   = src
INCLUDE = include
OBJDIR   = build
BINDIR   = build

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -rf


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean mrproper doc

doc:
	doxygen doc/doc_config

clean:
	@$(rm) $(OBJECTS)
	@$(rm) doc/html
	@$(rm) doc/latex
	@echo "Cleanup complete!"

mrproper: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Project is clean"
