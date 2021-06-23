# use g++
CXX = g++
CXXFLAGS ?= -Wall -pedantic -g -O0
TEST = out/tests/GraphWTest.o
RM ?= rm -f
INC = -Isrc/graph -Isrc/algorithm
DEST = out
SRC = src

_LIBGRAPH = graphw.hpp vertexw.hpp
# LIBGRAPH = $(_LIBGRAPH:%=$(DEST)/graph/%)

all: clean test

test: $(TEST)

$(TEST): tests/GraphWTest.cpp $(_LIBGRAPH)
	$(CXX) -o $@ $(CXXFLAGS) $(INC) $< $(LIBGRAPH)

$(_LIBGRAPH):
	

# $(DEST)/graph/%.o: $(SRC)/graph/%.cpp
# 	$(CXX) -c -o $@ $(CXXFLAGS) $(INC) $<

.PHONY: clean
clean:
	$(RM) $(OUTFILES) out/tests/*.o
