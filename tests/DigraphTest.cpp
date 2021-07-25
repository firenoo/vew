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
	//hasEdge
	assert(g.hasEdge(0, 2));
	assert(g.hasEdge(1, 2));
	assert(g.hasEdge(2, 3));
	assert(g.hasEdge(2, 4));
	assert(g.hasEdge(3, 5));
	assert(g.hasEdge(4, 5));
	assert(g.hasEdge(5, 6));
	assert(g.hasEdge(3, 6));
	assert(g.hasEdge(6, 3));
	assert(!g.hasEdge(0, 5));
	assert(!g.hasEdge(0, 10));
	assert(!g.hasEdge(-1, 10));
	const int A = 0, B = 2;	
	assert(g.hasEdge(A, B));
	assert(g.hasEdge(0, B));
	assert(g.hasEdge(A, 2));
	const int C = 10;
	assert(!g.hasEdge(C, 5));
	assert(!g.hasEdge(0, C));

	//getEdges
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
	auto s2 = g.getEdge(0, 5);
	assert(!s2);
	
	//Get list of all vertices
	auto vertices = g.vertices();
	assert(vertices.size() == 8);
	for(auto& v : vertices) {
		std::printf("%d ", **v);
	}
	std::printf("\n");
	//Get list of all edges
	auto edges = g.edges();
	assert(edges.size() == 9);
	for(auto& [v, e] : edges) {
		std::printf("(%d, %d)", **v, **(e.target()));
	}
	std::printf("\n");
	
	//Reverse	
	DirectedGraph<int> gr;
	g.reverse(gr);
	auto verticesr = gr.vertices();
	assert(verticesr.size() == 8);
	for(auto& v : verticesr) {
		std::printf("%d ", **v);
	}
	std::printf("\n");
	//Get list of all edges
	auto edgesr = gr.edges();
	//assert(edgesr.size() == 9);
	for(auto& [v, e] : edgesr) {
		std::printf("(%d, %d)", **v, **(e.target()));
	}
	std::printf("\n");
	assert(gr.vertexCount() == g.vertexCount());
	assert(gr.edgeCount() == g.edgeCount());
	
	assert(gr.hasEdge(2, 0));
	assert(gr.hasEdge(2, 1));
	assert(gr.hasEdge(3, 2));
	assert(gr.hasEdge(4, 2));
	assert(gr.hasEdge(5, 3));
	assert(gr.hasEdge(5, 4));
	assert(gr.hasEdge(6, 5));
	assert(gr.hasEdge(3, 6));
	assert(gr.hasEdge(6, 3));

	assert(gr.getEdge(2, 0));
	assert(gr.getEdge(2, 0).value() == 1.0);
	assert(gr.getEdge(2, 1));
	assert(gr.getEdge(2, 1).value() == 2.0);
	assert(gr.getEdge(3, 2));
	assert(gr.getEdge(3, 2).value() == 5.0);
	assert(gr.getEdge(4, 2));
	assert(gr.getEdge(4, 2).value() == 1.5);
	assert(gr.getEdge(5, 3));
	assert(gr.getEdge(5, 3).value() == 2.2);
	assert(gr.getEdge(5, 4));
	assert(gr.getEdge(5, 4).value() == 3.6);
	assert(gr.getEdge(6, 5));
	assert(gr.getEdge(6, 5).value() == 9.2);
	assert(gr.getEdge(6, 3));
	assert(gr.getEdge(6, 3).value() == 7.0);
	assert(gr.getEdge(3, 6));
	assert(gr.getEdge(3, 6).value() == 2.0);
	//Remove edges
	assert(g.removeEdge(0, 2));
	assert(!g.removeEdge(8, 19));
	assert(!g.removeEdge(0, C));
	assert(!g.removeEdge(C, 0));

	//Remove vertices

	//Clear
	g.clear();
	assert(g.edgeCount() == 0);
	assert(g.vertexCount() == 0);
	

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
	digraph_2();
}


}

}
int main() {
	firenoo::test::testSuite1();
	// firenoo::test::testSuite2();
}