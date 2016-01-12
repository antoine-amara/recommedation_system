CXX = g++
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
CXXFLAGS = -Iinclude/ -W -Wall -ansi -pedantic
LDFLAGS = -lgsl -lgslcblas -lm
EXEC = recommender_system

all: $(EXEC)

recommender_system: $(OBJ_FILES) main.o
	$(CXX) -o build/$@ $^ $(LDFLAGS)

$(OBJ_FILES): $(CPP_FILES)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper doc

doc:
	doxygen doc/doc_config

clean:
	rm -rf build/*.o

mrproper: clean
	rm -rf build/$(EXEC)
	rm -rf doc/html re
	rm -rf doc/latex
