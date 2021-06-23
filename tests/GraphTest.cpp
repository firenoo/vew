#include <vector>
#include <exception>
#include <cassert>
#include <iostream>
#include "graphw.hpp"
#include "graphwb.hpp"
#include "presets.hpp"

namespace firenoo {

namespace test {

void testAddVertex(firenoo::GraphW<int>& g, unsigned int testCt) {
	g.clear();
	for(unsigned int i = 0; i < testCt; ++i) {
		int r = i;
		g.addVertex(r);
		assert(g.hasVertex(r));
	}
	assert(g.hasVertex(0));
	assert(g.vertexCount() == testCt);
}

// void testRemoveEdge(firenoo::GraphW<int>& g);

// void testEdge(firenoo::GraphW<int>& g);




}

}
int main() {
	firenoo::GraphW<int> graphw;
	firenoo::test::testAddVertex(graphw, 100);

	firenoo::GraphWB<int> petersen = firenoo::undirected::petersen(1.0);
	assert(petersen.vertexCount() == 10);
	assert(petersen.edgeCount() == 15);

	firenoo::GraphWB<int> chvatal = firenoo::undirected::chavatal(1.0);
	assert(chvatal.vertexCount() == 12);
	assert(chvatal.edgeCount() == 24);
	std::cout << "All tests passed." << std::endl;
}