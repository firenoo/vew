# use g++
CXX = g++
CXXFLAGS ?= -Wall -pedantic -g -O0 -std=c++17
RM ?= rm -f
INC = -Isrc/graph -Isrc/algorithm
DEST = out
SRC = src


DISJOINTSET = out/disjointset/disjointset.o
TEST = out/tests/DigraphTest out/tests/UdigraphTest
_LIBGRAPH = digraph.hpp udigraph.hpp
# _ALGOS = presets.hpp search.hpp
LIBGRAPH = $(_LIBGRAPH:%=$(SRC)/graph/%)
ALGOS = $(_ALGOS:%=$(SRC)/algorithm/%)
all: clean test

test: $(TEST)

digraphtest: out/tests/DigraphTest

udigraphtest: out/tests/UdigraphTest

Example.o : tests/Example.cpp disjointset
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< src/algorithm/disjointset.cpp

disjointset: $(DISJOINTSET)

$(DISJOINTSET): src/algorithm/disjointset.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) -Isrc/algorithm $<

$(TEST): $(DEST)/tests/%: tests/%.cpp disjointset $(LIBGRAPH) 
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(DISJOINTSET) $(LIBGRAPH) 

.PHONY: clean
clean:
	$(RM) $(OUTFILES) out/tests/*.o
