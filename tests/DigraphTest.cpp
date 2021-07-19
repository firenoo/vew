#include <vector>
#include <exception>
#include <cassert>
#include <iostream>
#include "digraph.hpp"
#include "presets.hpp"
#include "search.hpp"
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
void testdfs_cc();
void testdfs_full();
void testReversal();
void test_top_sort();
/*
 * Test Suite 1 - basic functions
 * - add vertex
 * - remove vertex
 * - add edge
 * - delete edge
 * - clear
 */
void testSuite1() {
	digraph_1();

}

/*
 * Test Suite 2
 * - dfs 1
 * - dfs 2
 * - top sort
 */
void testSuite2() {
	testdfs_cc();
	testdfs_full();
	test_top_sort();
}

void testdfs_cc() {
	DirectedGraph<int> g;
	g.addVertex(0);
	g.addVertex(1);

	g.addEdge(0, 1, 1.0);
	auto dfs = dfs_cc<int>(g, {});
	assert(dfs.size() == 1);
	auto comp = *dfs[0];
	assert(comp.size() == 2);
	for(auto v : comp) {
		assert(g.hasVertex(v->get()));
	}
	delete dfs[0];
}

void testdfs_full() {
	DirectedGraph<int> g;
	g.addVertex(0);
	g.addVertex(1);

	g.addEdge(0, 1, 1.0);
	auto dfs = dfs_cc<int>(g, {});
	assert(dfs.size() == 1);
	auto comp = *dfs[0];
	assert(comp.size() == 2);
	for(auto v : comp) {
		assert(g.hasVertex(v->get()));
	}
	delete dfs[0];
}

void testReversal(){
	DirectedGraph<int> g;
	const double WEIGHT = 0;
	g.addVertex(0);
	g.addVertex(1);
	g.addVertex(2);

	g.addEdge(0, 1, WEIGHT);
	g.addEdge(0, 2, WEIGHT);
	g.addEdge(1, 2, WEIGHT);

	DirectedGraph<int> gr = g.r();
	assert(gr.hasEdge(1, 0));
	assert(gr.hasEdge(2, 1));
	assert(gr.hasEdge(2, 0));
}

void test_top_sort() {
	DirectedGraph<int> g;
	const double WEIGHT = 0;
	for(unsigned int i = 0; i < 10; ++i) {
		g.addVertex(i);
	}
	for(unsigned int i = 0; i < 9; ++i) {
		g.addEdge(i, i+1, WEIGHT);
	}
	auto sort = firenoo::top_sort(g);
	int i = 0;
	for(auto it = sort.begin(); it != sort.end(); ++it) {
		assert(it->_vertex->get() == i);
		i++;
	}
}

}

}
int main() {
	firenoo::test::testSuite1();
	// firenoo::test::testSuite2();
	// firenoo::DirectedGraph<int> g;
}