CXX = g++
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
CXXFLAGS = -Iinclude/ -W -Wall -ansi -pedantic -std=c++11
LDFLAGS = -lgsl -lgslcblas -lm
EXEC = recommender_system

all: $(EXEC)

main.o: main.cpp
	$(CXX) -o build/$@ $^ $(LDFLAGS)

recommender_system: $(OBJ_FILES) main.o
	$(CXX) -o build/$@ $^ $(LDFLAGS)

$(OBJ_FILES): $(CPP_FILES)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper doc

doc:
	doxygen doc/doc_config

clean:
	rm -f *.o
	rm -rf build/*.o

mrproper: clean
	rm -rf build/$(EXEC)
	rm -rf doc/html re
	rm -rf doc/latex
