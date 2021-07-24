#include <vector>
#include <exception>
#include <cassert>
#include <iostream>
#include "digraph.hpp"
// #include "presets.hpp"
// #include "search.hpp"
namespace firenoo {

//Test Suite
namespace test {

void digraph_1() {
	DirectedGraph<int> g;
	for(int i = 0; i < 8; ++i) {
		g.addVertex(i);
	}
	assert(g.addEdge(0, 2, 1.0));
	assert(g.addEdge(1, 2, 2.0));
	assert(g.addEdge(2, 3, 5.0));
	assert(g.addEdge(2, 4, 1.5));
	assert(g.addEdge(3, 5, 2.2));
	assert(g.addEdge(4, 5, 3.6));
	assert(g.addEdge(5, 6, 9.2));
	assert(g.addEdge(3, 6, 7.0));
	assert(!g.addEdge(3, 6, 1.0));
	assert(!g.addBiEdge(3, 6, 2.0));
	//Basic Facts
	assert(g.vertexCount() == 8);
	assert(g.edgeCount() == 9);	
	//Vertices
	for(int i = 0; i < 8; ++i) {
		assert(g.hasVertex(i));
	}

	//Edges
	assert(g.hasEdge(0, 2));
	assert(g.hasEdge(1, 2));
	assert(g.hasEdge(2, 3));
	assert(g.hasEdge(2, 4));
	assert(g.hasEdge(3, 5));
	assert(g.hasEdge(4, 5));
	assert(g.hasEdge(5, 6));
	assert(g.hasEdge(3, 6));
	assert(g.hasEdge(6, 3));

	assert(g.getEdge(0, 2));
	assert(g.getEdge(0, 2).value() == 1.0);
	assert(g.getEdge(1, 2));
	assert(g.getEdge(1, 2).value() == 2.0);
	assert(g.getEdge(2, 3));
	assert(g.getEdge(2, 3).value() == 5.0);
	assert(g.getEdge(2, 4));
	assert(g.getEdge(2, 4).value() == 1.5);
	assert(g.getEdge(3, 5));
	assert(g.getEdge(3, 5).value() == 2.2);
	assert(g.getEdge(4, 5));
	assert(g.getEdge(4, 5).value() == 3.6);
	assert(g.getEdge(5, 6));
	assert(g.getEdge(5, 6).value() == 9.2);
	assert(g.getEdge(3, 6));
	assert(g.getEdge(3, 6).value() == 7.0);
	assert(g.getEdge(6, 3));
	assert(g.getEdge(6, 3).value() == 2.0);

	//Fake edges
	auto s2 = g.getEdge(0, 5);
	assert(!s2);
}

void digraph_2() {
	DirectedGraph<int> g;
	//Remove vertex: simple
	g.addVertex(0);
	g.addVertex(2);
	
	assert(g.removeVertex(2));
	
}

void testSuite1();
void testSuite2();

void testSuite1() {
	digraph_1();

}


}

}
int main() {
	firenoo::test::testSuite1();
	// firenoo::test::testSuite2();
}