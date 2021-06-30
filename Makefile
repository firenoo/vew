# use g++
CXX = g++
CXXFLAGS ?= -Wall -pedantic -g -O0
RM ?= rm -f
INC = -Isrc/graph -Isrc/algorithm
DEST = out
SRC = src

TEST = out/tests/GraphWTest.o out/tests/GraphWBTest.o
_LIBGRAPH = graphw.hpp vertexw.hpp
_ALGOS = presets.hpp search.hpp
LIBGRAPH = $(_LIBGRAPH:%=$(SRC)/graph/%)
ALGOS = $(_ALGOS:%=$(SRC)/algorithm/%)
all: clean test

test: $(TEST)


# $(TEST): $(_TESTS) $(_LIBGRAPH)
# 	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(LIBGRAPH)

$(TEST): $(DEST)/tests/%.o: tests/%.cpp $(LIBGRAPH) $(ALGOS)
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(LIBGRAPH) $(ALGOS)

.PHONY: clean
clean:
	$(RM) $(OUTFILES) out/tests/*.o
