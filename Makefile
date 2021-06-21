# use g++
CXX = g++
CXXFLAGS ?= -Wall -pedantic -g -O0
TEST = out/tests/GraphTest.o
RM ?= rm -f
INC = -Isrc/graph
DEST = out
SRC = src

_LIBGRAPH = graphw.o graph_vertex.o
LIBGRAPH = $(_LIBGRAPH:%=$(DEST)/graph/%)

all: clean test

test: $(TEST)

$(TEST): tests/GraphTest.cpp libgraph
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(LIBGRAPH)


libgraph: $(LIBGRAPH)

$(DEST)/graph/%.o: $(SRC)/graph/%.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INC) $<

.PHONY: clean
clean:
	$(RM) $(OUTFILES) out/*.o
