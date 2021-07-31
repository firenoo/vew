#include <vector>
#include <exception>
#include <cassert>
#include <iostream>
#include "digraph.hpp"
#define _FN_ENABLE_DIRECTED_PRESETS
#include "presets.hpp"
// #include "search.hpp"
namespace firenoo {

//Test Suite
namespace test {

	void testSuite1();
	void digraph1();
	void digraph2();
	void copyTest();
	void moveTest();

	void testSuite2();
	void path();
	void chain();

	void digraph1() {
		std::printf("Test 1\n");
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
		///////////////////////////////////////////////////////////////////////////
		//Reverse tests.
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
		//Reverse tests end
		///////////////////////////////////////////////////////////////////////////
		//Remove edges
		assert(g.removeEdge(0, 2));
		assert(!g.removeEdge(8, 19));
		assert(!g.removeEdge(0, C));
		assert(!g.removeEdge(C, 0));
		assert(!g.hasEdge(0, 2));
		assert(!g.getEdge(0, 2));
		
		//Remove vertices
		assert(g.removeVertex(0));
		assert(!g.hasVertex(0));
		assert(g.removeVertex(2));
		assert(!g.hasVertex(2));
		assert(!g.hasEdge(1, 2));
		assert(!g.hasEdge(2, 5));
		assert(!g.hasEdge(2, 4));
		assert(g.edges().size() == 5);
		assert(g.vertices().size() == 6);
		assert(!g.removeVertex(0));
		assert(!g.removeVertex(C));
		//Clear
		g.clear();
		assert(g.edgeCount() == 0);
		assert(g.vertexCount() == 0);
		std::printf("-------------------------\n");
	}

	void digraph2() {
		std::printf("Test 2\n");
		DirectedGraph<int> g;
		//Remove vertex: simple
		g.addVertex(0);
		g.addVertex(2);
		
		assert(g.removeVertex(2));
		
		g.addVertex(1);
		g.addVertex(2);
		g.addVertex(3);
		//Add BiEdge
		assert(g.hasVertex(2));
		assert(g.addBiEdge(0, 1, 1.0));
		const int A = 0, B = 2;
		assert(g.addBiEdge(A, B, 2.0));
		assert(g.addBiEdge(3, A, 3.0));
		assert(g.addBiEdge(B, 3, 4.0));
		assert(!g.addBiEdge(A, B, 1.0));
		assert(!g.addBiEdge(3, A, 1.0));
		assert(!g.addBiEdge(B, 3, 4.0));
		//Remove Edge
		assert(g.removeEdge(3, A));
		assert(g.removeEdge(A, 3));	
		assert(!g.hasEdge(3, A));
		assert(!g.getEdge(3, A));
		assert(!g.hasEdge(3, A));
		assert(!g.getEdge(A, 3));
		//Remove Vertex
		assert(g.removeVertex(0));
		assert(!g.hasVertex(0));
		assert(!g.hasEdge(0, 1));
		assert(!g.getEdge(0, 1));
		assert(!g.hasEdge(1, 0));
		assert(!g.getEdge(1, 0));
		assert(!g.hasEdge(A, B));
		assert(!g.getEdge(A, B));
		assert(!g.hasEdge(B, A));
		assert(!g.getEdge(B, A));
		std::printf("-------------------------\n");
	}

	void copyTest() {
		std::printf("Copy test\n");
		DirectedGraph<int> g;
		for(int i = 0; i < 10; ++i) {
			g.addVertex(i);
		}
		DirectedGraph<int> copy = g;
		for(int i = 0; i < 10; ++i) {
			assert(copy.hasVertex(i));
		}
		g.addVertex(10);
		assert(!copy.hasVertex(10));
		g.addEdge(0, 1, 1.0);
		assert(!copy.hasEdge(0, 1));

		copy.addVertex(100);
		assert(!g.hasVertex(100));
		copy.addEdge(2, 3, 1.0);
		assert(!g.hasEdge(2, 3));
		std::printf("---------------------------------\n");
	}

	void moveTest() {
		std::printf("Move test\n");
		DirectedGraph<int> g;
		for(int i = 0; i < 10; ++i) {
			g.addVertex(i);
		}
		DirectedGraph<int> move = g;
		for(int i = 0; i < 10; ++i) {
			assert(g.hasVertex(i));
		}
		std::printf("---------------------------------\n");
	}

	void testSuite1() {
		std::printf("Directed Graph Tests\n----------------------------\n");
		digraph1();
		digraph2();
		copyTest();
		moveTest();
	}

	void testSuite2() {
		std::printf("Preset Tests\n-----------------------\n");
		path();
		chain();
	}

	void path() {
		std::printf("Path test\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		DirectedGraph<int> g = directed::makePath(LENGTH, WEIGHT);
		for(auto &v : g) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto &[vertex, edge] : g.edges()) {
			std::printf("(%d, %d) ", **vertex, **(edge.target()));
		}
		std::printf("\n");
		std::cout.flush();
		for(std::size_t i = 0; i < LENGTH; ++i) {
			assert(g.hasVertex((int)i));
		}
		for(std::size_t i = 0; i < LENGTH - 1; ++i) {
			assert(g.hasEdge(i, i+1));
			assert(g.getEdge(i, i+1));
			assert(g.getEdge(i, i+1).value() == WEIGHT);
		}
	}

	void chain() {

	}

}

}
int main() {
	firenoo::test::testSuite1();
	// firenoo::test::testSuite2();
}