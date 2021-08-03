#include <vector>
#include <exception>
#include <cassert>
#include <iostream>
#include "digraph.hpp"
#include "search.hpp"
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
	void cycle();
	void complete();

	void testSuite3();
	void simpleDFSTest();
	void fullDFSTest();
	void cycleTest();
	void topSortTest();

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
		std::printf("Success\n---------------------------------\n");
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
		std::printf("Success\n---------------------------------\n");
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
		std::printf("Success\n---------------------------------\n");
	}

	void moveTest() {
		std::printf("Move test\n");
		DirectedGraph<int> g;
		for(int i = 0; i < 10; ++i) {
			g.addVertex(i);
		}
		DirectedGraph<int> move = std::move(g);
		for(int i = 0; i < 10; ++i) {
			assert(move.hasVertex(i));
		}
		std::printf("Success.\n---------------------------------\n");
	}

	void testSuite1() {
		std::printf("Directed Graph Tests\n----------------------------\n");
		digraph1();
		digraph2();
		copyTest();
		moveTest();
		std::printf("Directed Graph Tests Succeeded.\n");
	}

	void testSuite2() {
		std::printf("Preset Tests\n-----------------------\n");
		path();
		chain();
		cycle();
		complete();
		std::printf("Presets Tests Succeeded.\n");
	}

	void path() {
		std::printf("Path test\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		DirectedGraph<int> g = directed::makePath(LENGTH, WEIGHT);
		for(auto& v : g) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto& [vertex, edge] : g.edges()) {
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
		std::printf("Success\n---------------------------------\n");
		std::printf("2WayPath test\n");
		DirectedGraph<int> g2 = directed::make2WayPath(LENGTH, WEIGHT);
		for(auto& v : g2) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto& [vertex, edge] : g2.edges()) {
			std::printf("(%d, %d) ", **vertex, **(edge.target()));
		}
		std::printf("\n");
		std::cout.flush();
		for(std::size_t i = 0; i < LENGTH; ++i) {
			assert(g2.hasVertex((int)i));
		}
		for(std::size_t i = 0; i < LENGTH - 1; ++i) {
			assert(g2.hasEdge(i, i+1));
			assert(g2.hasEdge(i+1, i));
		}
		std::printf("Success\n---------------------------------\n");
	}

	void chain() {
		std::printf("Chain Test\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		DirectedGraph<int> g = directed::makeChain(LENGTH, WEIGHT);
		for(auto& v : g) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto& [vertex, edge] : g.edges()) {
			std::printf("(%d, %d) ", **vertex, **(edge.target()));
		}
		std::printf("\n");
		std::cout.flush();
		for(std::size_t i = 0; i < LENGTH * 3 + 1; ++i) {
			assert(g.hasVertex((int) i));
		}
		for(std::size_t i = 0; i < LENGTH - 1; ++i) {
			assert(g.hasEdge(i * 3, i * 3 + 1));
			assert(g.hasEdge(i * 3, i * 3 + 2));
			assert(g.hasEdge(i * 3 + 1, (i+1) * 3));
			assert(g.hasEdge(i * 3 + 2, (i+1) * 3));
		} 
		std::printf("Success\n---------------------------------\n");
		std::printf("2WayChain Test\n");
		DirectedGraph<int> g2 = directed::make2WayChain(LENGTH, WEIGHT);
		for(auto& v : g2) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto& [vertex, edge] : g2.edges()) {
			std::printf("(%d, %d) ", **vertex, **(edge.target()));
		}
		std::printf("\n");
		std::cout.flush();
		for(std::size_t i = 0; i < LENGTH * 3 + 1; ++i) {
			assert(g2.hasVertex((int) i));
		}
		for(std::size_t i = 0; i < LENGTH - 1; ++i) {
			assert(g2.hasEdge(i * 3, i * 3 + 1));
			assert(g2.hasEdge(i * 3, i * 3 + 2));
			assert(g2.hasEdge(i * 3 + 1, (i+1) * 3));
			assert(g2.hasEdge(i * 3 + 2, (i+1) * 3));
			assert(g2.hasEdge(i * 3 + 1, i * 3));
			assert(g2.hasEdge(i * 3 + 2, i * 3));
			assert(g2.hasEdge((i+1) * 3, i * 3 + 1));
			assert(g2.hasEdge((i+1) * 3, i * 3 + 2));
		} 
		std::printf("Success\n---------------------------------\n");
	}

	void cycle() {
		std::printf("Cycle Graph Test\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		DirectedGraph<int> g = directed::makeCycle(LENGTH, WEIGHT);
		for(auto& v : g) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto& [vertex, edge] : g.edges()) {
			std::printf("(%d, %d) ", **vertex, **(edge.target()));
		}
		std::printf("\n");
		std::cout.flush();
		for(std::size_t i = 0; i < LENGTH - 1; ++i) {
			assert(g.hasEdge(i, i+1));
		}
		assert(g.hasEdge(LENGTH-1, 0));
		std::printf("Success\n---------------------------------\n");
		std::printf("2WayCycle Graph Test\n");
		DirectedGraph<int> g2 = directed::make2WayCycle(LENGTH, WEIGHT);
		for(auto& v : g2) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto& [vertex, edge] : g2.edges()) {
			std::printf("(%d, %d) ", **vertex, **(edge.target()));
		}
		std::printf("\n");
		std::cout.flush();
		for(std::size_t i = 0; i < LENGTH - 1; ++i) {
			assert(g2.hasEdge(i, i+1));
			assert(g2.hasEdge(i+1, i));
		}
		assert(g2.hasEdge(LENGTH-1, 0));
		assert(g2.hasEdge(0, LENGTH-1));
		std::printf("Success\n---------------------------------\n");
	}

	void complete() {
		std::printf("Complete Graph Test\n");
		const std::size_t SIZE = 5;
		const double WEIGHT = 1.0;
		DirectedGraph<int> g = directed::makeComplete(SIZE, WEIGHT);
		for(auto& v : g) {
			std::printf("%d ", v.first);
		}
		std::printf("\n");
		for(auto& [vertex, edge] : g.edges()) {
			std::printf("(%d, %d) ", **vertex, **(edge.target()));
		}
		std::printf("\n");
		std::cout.flush();
		assert(g.edgeCount() == (SIZE * (SIZE- 1)));
		for(std::size_t i = 0; i < SIZE; ++i) {
			assert(g.hasVertex((int) i));
		}
		for(std::size_t i = 0; i < SIZE - 1; ++i) {
			for(std::size_t j = i + 1; j < SIZE; ++j) {
				assert(g.hasEdge(i, j));
			}
		}
		std::printf("Success\n---------------------------------\n");
	}

	void testSuite3() {
		std::printf("DFS Tests\n");
		simpleDFSTest();
		fullDFSTest();
		cycleTest();
		topSortTest();
		std::printf("DFS Tests Successful.\n-----------------------\n");
	}

	void simpleDFSTest() {
		std::printf("Simple DFS Test\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		//PATH
		std::printf("Path:\n");
		DirectedGraph<int> path = directed::makePath(LENGTH, WEIGHT);
		auto resultPath1 = simpleDFS(path);
		assert(resultPath1.size() == 1);
		for(auto& it : resultPath1) {
			for(auto& v : it) {
				std::printf("%d ", **v);
			}
			std::printf("\n");
		}
		auto resultPath2 = simpleDFS(path, {0});
		assert(resultPath2.size() == 1);
		for(auto& it : resultPath2) {
			for(auto& v : it) {
				std::printf("%d ", **v);
			}
			std::printf("\n");
		}
		
		//CHAIN
		std::printf("Chain:\n");
		DirectedGraph<int> chain = directed::makeChain(LENGTH, WEIGHT);
		auto resultChain1 = simpleDFS(chain);
		assert(resultChain1.size() == 1);
		for(auto& it : resultChain1) {
			for(auto& v : it) {
				std::printf("%d ", **v);
			}
			std::printf("\n");
		}
		auto resultChain2 = simpleDFS(chain, {5});
		assert(resultChain2.size() == 1);
		for(auto& it : resultChain2) {
			for(auto& v : it) {
				std::printf("%d ", **v);
			}
			std::printf("\n");
		}
		//CYCLE
		std::printf("Cycle:\n");
		DirectedGraph<int> cycle = directed::makeCycle(LENGTH, WEIGHT);
		auto resultCycle1 = simpleDFS(cycle);
		assert(resultCycle1.size() == 1);
		for(auto& it : resultCycle1) {
			for(auto& v : it) {
				std::printf("%d ", **v);
			}
			std::printf("\n");
		}
		auto resultCycle2 = simpleDFS(cycle, {0});
		assert(resultCycle2.size() == 1);
		for(auto& it : resultCycle2) {
			for(auto& v : it) {
				std::printf("%d ", **v);
			}
			std::printf("\n");
		}
		std::printf("Success\n---------------------------------\n");
	}

	void fullDFSTest() {
		std::printf("Full DFS Test\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		//PATH
		std::printf("Path:\n");
		DirectedGraph<int> path1 = directed::makePath(LENGTH, WEIGHT);
		auto resultPath1 = fullDFS(path1);
		assert(resultPath1.size() == 1);
		for(auto& it : resultPath1) {
			for(auto& v : it) {
				std::printf("{%lu, %lu | %d} ", std::get<0>(v), std::get<1>(v), **std::get<2>(v));
			}
			std::printf("\n");
		}
		auto resultPath2 = fullDFS(path1, {0});
		assert(resultPath2.size() == 1);
		for(auto& it : resultPath2) {
			for(auto& v : it) {
				std::printf("{%lu, %lu | %d} ", std::get<0>(v), std::get<1>(v), **std::get<2>(v));
			}
			std::printf("\n");
		}
		
		//CHAIN
		std::printf("Chain:\n");
		DirectedGraph<int> chain1 = directed::makeChain(2, WEIGHT);
		auto resultChain1 = fullDFS(chain1);
		assert(resultChain1.size() == 1);
		for(auto& it : resultChain1) {
			for(auto& v : it) {
				std::printf("{%lu, %lu | %d} ", std::get<0>(v), std::get<1>(v), **std::get<2>(v));
			}
			std::printf("\n");
		}
		auto resultChain2 = fullDFS(chain1, {0});
		assert(resultChain2.size() == 1);
		for(auto& it : resultChain2) {
			for(auto& v : it) {
				std::printf("{%lu, %lu | %d} ", std::get<0>(v), std::get<1>(v), **std::get<2>(v));
			}
			std::printf("\n");
		}
		std::printf("Success\n---------------------------------\n");
	}

	void cycleTest() {
		std::printf("Cycle Tests\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		DirectedGraph<int> cGraph = directed::makeCycle(LENGTH, WEIGHT);
		assert(hasCycle(cGraph));

		DirectedGraph<int> pGraph = directed::makePath(LENGTH, WEIGHT);
		assert(!hasCycle(pGraph));

		DirectedGraph<int> kGraph = directed::makeComplete(LENGTH, WEIGHT);
		assert(hasCycle(kGraph));
		std::printf("Success\n---------------------------------\n");
	}

	void topSortTest() {
		std::printf("Top Sort Tests\n");
		const std::size_t LENGTH = 5;
		const double WEIGHT = 1.0;
		DirectedGraph<int> g = directed::makePath(LENGTH, WEIGHT);
		auto resultTS = topSort(g);
		for(auto i : resultTS) {
			std::printf("%d ", **i);
		}
		std::printf("\n");
		std::printf("Success\n---------------------------------\n");
	}

}

}
int main() {
	firenoo::test::testSuite1();
	firenoo::test::testSuite2();
	firenoo::test::testSuite3();
}