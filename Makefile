# use g++
CXX = g++
CXXFLAGS ?= -Wall -pedantic -g -O0 -std=c++17
RM ?= rm -f
INC = -Isrc/graph -Isrc/algorithm -Isrc/utils
DEST = out
SRC = src


DISJOINTSET = out/disjointset/disjointset.o
PRESETS = out/utils/presets.o
DIGRAPHTEST = out/tests/DigraphTest
UDIGRAPHTEST = out/tests/UDigraphTest
_LIBGRAPH = digraph.hpp udigraph.hpp
# _ALGOS = presets.hpp search.hpp
LIBGRAPH = $(_LIBGRAPH:%=$(SRC)/graph/%)
ALGOS = $(_ALGOS:%=$(SRC)/algorithm/%)
all: clean test

test: digraphtest udigraphtest

digraphtest: $(DIGRAPHTEST)
	./$(DIGRAPHTEST)
udigraphtest: $(UDIGRAPHTEST)
	
disjointset: $(DISJOINTSET)

presets: $(PRESETS)

Example.o : tests/Example.cpp disjointset
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< src/algorithm/disjointset.cpp

$(PRESETS) : src/utils/presets.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INC) $<

$(DISJOINTSET): src/algorithm/disjointset.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) -Isrc/algorithm $<

$(DIGRAPHTEST): tests/DigraphTest.cpp disjointset presets
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(DISJOINTSET) $(PRESETS)

$(UDIGRAPHTEST): tests/UDigraphTest.cpp disjointset presets
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(DISJOINTSET) $(PRESETS)

.PHONY: clean
clean:
	$(RM) $(OUTFILES) out/tests/*.o
