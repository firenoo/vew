# use g++
CXX = g++
CXXFLAGS ?= -Wall -pedantic -g -O0 -std=c++17
RM ?= rm -f
INC = -Isrc/graph -Isrc/algorithm
DEST = out
SRC = src

TEST = out/tests/DigraphTest.o out/tests/UdigraphTest.o
_LIBGRAPH = digraph.hpp vertexw.hpp
_ALGOS = presets.hpp search.hpp disjointset.cpp
LIBGRAPH = $(_LIBGRAPH:%=$(SRC)/graph/%)
ALGOS = $(_ALGOS:%=$(SRC)/algorithm/%)
all: clean test

test: $(TEST)

Example.o : tests/Example.cpp src/algorithm/disjointset.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< src/algorithm/disjointset.cpp


# $(TEST): $(_TESTS) $(_LIBGRAPH)
# 	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(LIBGRAPH)

$(TEST): $(DEST)/tests/%.o: tests/%.cpp $(LIBGRAPH) $(ALGOS)
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(LIBGRAPH) $(ALGOS)

.PHONY: clean
clean:
	$(RM) $(OUTFILES) out/tests/*.o
