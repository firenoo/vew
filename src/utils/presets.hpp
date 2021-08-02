#ifndef _FN_PRESETS
	#define _FN_PRESETS 
	#include "digraph.hpp"
	#include "udigraph.hpp"
/*
 * Presets
 * The functions in this file construct predefined graphs.
 */
namespace firenoo {

#ifdef _FN_ENABLE_UNDIRECTED_PRESETS
	namespace undirected {

		/*
		* Constructs an undirected line graph with `n` vertices, with each
		* edge having weight `w`. Vertices are labeled `0` to `n-1`.
		*/
		UndirectedGraph<int> makeLine(int n, double w);

		/*
		* Constructs a complete graph with `n` vertices, with each
		* edge having weight `w`.
		*/
		UndirectedGraph<int> makeComplete(int n, double w);

		/*
		* Constructs a cycle graph with `n` vertices, with each
		* edge having weight `w`.
		*/
		UndirectedGraph<int> makeCycle(int n, double w);

		/*
		* Constructs a lattice graph with `n*m` vertices, with each
		* edge having weight `w`.
		* Vertices are labeled `0` to `n*m-1`. 
		*/
		UndirectedGraph<int> makeLattice(int n, int m, double w);

		/*
		* Constructs a torus graph with `n x m` vertices, with each
		* edge having weight `w`.
		*/
		UndirectedGraph<int> makeTorus(int n, int m, double w);

		/*
		* Constructs a 3-cube graph. 8 vertices, 12 edges.
		*/
		UndirectedGraph<int> makeCube3(double w);

		/*
		* Constructs the Petersen graph. 10 vertices, 15 edges.
		* Vertices are labeled 0-9.
		* Edges have weight `w`.
		*/
		UndirectedGraph<int> makePetersen(double w);

		/*
		* Constructs the Chvátal graph. 12 vertices, 24 edges.
		* Vertices are labeled 0-11.
		* Edges have weight `w`.
		*/
		UndirectedGraph<int> makeChavatal(double w);


		UndirectedGraph<int> makeLine(int n, double w) {
			UndirectedGraph<int> g;
			for(int i = 0; i < n; ++i) {
				g.addVertex(i);
			}
			for(int i = 0; i < n-1; ++i) {
				g.addEdge(i, i+1, w);
			}
			return g;
		}

		UndirectedGraph<int> makeComplete(int n, double w) {
			UndirectedGraph<int> g;
			for(int i = 0; i < n; ++i) {
				g.addVertex(i);
			}
			for(int i = 0; i < n-2; ++i) {
				for(int j = i+1; j < n-1; ++j) {
					g.addEdge(i, j, w);
				}
			}
			return g;
		}

		UndirectedGraph<int> makeCycle(int n, double w) {
			UndirectedGraph<int> g = makeLine(n, w);
			g.addEdge(0, n-1, w);
			return g;
		}

		UndirectedGraph<int> makeLattice(int n, int m, double w) {
			UndirectedGraph<int> g ;
			for(int i = 0; i < n * m; ++i) {
				g.addVertex(i);
			}
			for(int i = 0; i < m-1; ++i) {
				//add horizontal edges
				for(int j = 0; j < n-1; ++j) {
					g.addEdge(i * n + j, i * n + j + 1, w);
				}
				//add vertical edges
				g.addEdge(i, i + n, w);
			}
			return g;
		}

		UndirectedGraph<int> makeTorus(int n, int m, double w) {
			UndirectedGraph<int> g = makeLattice(n, m, w);
			for(int i = 0; i < m; ++i) {
				//loop around - horizontal
				g.addEdge(i * n, (i + 1) * n - 1, w);
			}
			for(int i = 0; i < n; ++i) {
				//loop around - vertical
				g.addEdge(i, (m - 1) + i, w);
			}
			return g;
		}

		UndirectedGraph<int> makeCube3(double w) {
			UndirectedGraph<int> g;
			for(int i = 0; i < 8; ++i) {
				g.addVertex(i);
			}
			g.addEdge(0, 1, w);
			g.addEdge(0, 3, w);
			g.addEdge(0, 5, w);
			g.addEdge(1, 2, w);
			g.addEdge(1, 6, w);
			g.addEdge(2, 3, w);
			g.addEdge(2, 7, w);
			g.addEdge(3, 4, w);
			g.addEdge(4, 5, w);
			g.addEdge(4, 7, w);
			g.addEdge(5, 6, w);
			g.addEdge(6, 7, w);
			return g;
		}

		UndirectedGraph<int> makePetersen(double w) {
			UndirectedGraph<int> g;
			g.clear();
			for(unsigned int i = 0; i < 10; ++i) {
				g.addVertex(i);
			}
			g.addEdge(0, 1, w);
			g.addEdge(0, 5, w);
			g.addEdge(0, 4, w);
			g.addEdge(1, 2, w);
			g.addEdge(1, 6, w);
			g.addEdge(2, 3, w);
			g.addEdge(2, 7, w);
			g.addEdge(3, 4, w);
			g.addEdge(3, 8, w);
			g.addEdge(4, 9, w);
			g.addEdge(5, 7, w);
			g.addEdge(5, 8, w);
			g.addEdge(6, 8, w);
			g.addEdge(6, 9, w);
			g.addEdge(7, 9, w);
			return g;
		}
		
		UndirectedGraph<int> makeChavatal(double w) {
			UndirectedGraph<int> g;
			g.clear();
			for(unsigned int i = 0; i < 12; ++i) {
				g.addVertex(i);
			}
			g.addEdge(0,  1,  w);
			g.addEdge(0,  3,  w);
			g.addEdge(0,  5,  w);
			g.addEdge(0,  6,  w);
			g.addEdge(1,  2,  w);
			g.addEdge(1,  7,  w);
			g.addEdge(1,  8,  w);
			g.addEdge(2,  3,  w);
			g.addEdge(2,  9,  w);
			g.addEdge(2,  10, w);
			g.addEdge(3,  4,  w);
			g.addEdge(3,  11, w);
			g.addEdge(4,  5,  w);
			g.addEdge(4,  7,  w);
			g.addEdge(4,  8,  w);
			g.addEdge(5,  9,  w);
			g.addEdge(5,  10, w);
			g.addEdge(6,  7,  w);
			g.addEdge(6,  9,  w);
			g.addEdge(6,  10, w);
			g.addEdge(7,  11, w);
			g.addEdge(8,  9,  w);
			g.addEdge(8,  11, w);
			g.addEdge(10, 11, w);
			return g;
		}
	}
#endif
#ifdef _FN_ENABLE_DIRECTED_PRESETS
	namespace directed {

		/*
		 * Creates a directed graph with a path with the specified length.
		 * Nodes are labelled 0 to `length - 1`. 
		 * Edges are directed from lower value indices to higher value indices.
		 * For example, calling `makePath(2, w)` will create a directed graph 
		 * G = (V, E), with 
		 * V = {0, 1}, 
		 * E = {(0, 1)}.
		 * 
		 * Each edge has a weight of `w`.
		 * Will fail if length == 0.
		 */
		DirectedGraph<int> makePath(std::size_t length, double w);


		/*
		 * Creates a bi-directional line graph with the specified length.
		 * Nodes are labelled 0 to `length - 1`.
		 * The resultant graph is analogous to `undirected::makeLine`, using
		 * `DirectedGraph` instead of `UndirectedGraph`.
		 * For example, calling `make2WayPath(3, w) will create a directed graph
		 * G = (V, E) with
		 * V = {0, 1, 2}
		 * E = {(0, 1), (1, 0), (1, 2), (2, 1)}.
		 * 
		 * Each edge has a weight of `w`.
		 * Will fail if `length == 0`.
		 */
		DirectedGraph<int> make2WayPath(std::size_t length, double w);

		/*
		 * Creates a directed cyclic graph of the specified length.
		 * Nodes are labelled 0 to `length - 1`.
		 * For example, calling `makeCycle(3, w)` will create a directed graph
		 * G = (V, E) with
		 * V = {0, 1, 2}
		 * E = {(0, 1), (1, 2), (2, 0)}.
		 * 
		 * Each edge has a weight of `w`.
		 * Will fail if `length == 0`.
		 */
		DirectedGraph<int> makeCycle(std::size_t length, double w);

		/*
		 * Creates a cyclic graph of the specified length.
		 * Analogous to `undirected::makeCycle`.
		 * For example, calling `make2WayCycle(3, w)` will create a directed 
		 * graph
		 * G = (V, E) with
		 * V = {0, 1, 2}
		 * E = {(0, 1), (1, 0), (1, 2), (2, 1), (2, 0), (0, 2)}.
		 * 
		 * Each edge has a weight of `w`.
		 * Will fail if `length == 0`.
		 */
		DirectedGraph<int> make2WayCycle(std::size_t length, double w);

		/*
		 * Creates a complete directed graph with `size` nodes.
		 * Analogous to `undirected::makeComplete` for DirectedGraph.
		 * 
		 * Each edge has a weight `w`.
		 * Will fail if `size == 0`.
		 */
		DirectedGraph<int> makeComplete(std::size_t size, double w);

		/*
		 * Creates a one-directional chain graph with `length` links.
		 * Intuitively, a chain graph is a graph that looks like a
		 * linear chain link.
		 * Here, a link consists of 3 vertices and 4 edges, with 1
		 * vertex being the "head" and 2 vertices the "tail". Edges
		 * exist from head to tail within a link, as well as from tail
		 * to the head of the next link. At the end is a single link with
		 * only a head vertex; this is not counted as part of the `length`
		 * links. For a more precise description, see the formal definition
		 * below.
		 * 
		 * Formal definition:
		 * G = (V, E) with
		 * V = {0, 1, 2, ..., 3 * length + 1}
		 * E = {(3i, 3i + 1)     | 0 <= i < length} U 
		 *     {(3i, 3i + 2)     | 0 <= i < length} U
		 *     {(3i + 1, 3(i+1)) | 0 <= i < length} U
		 * 	   {(3i + 2, 3(i+1)) | 0 <= i < length}
		 */
		DirectedGraph<int> makeChain(std::size_t length, double w);

		/*
		 * Creates a two-directional chain graph with `length` links.
		 * Intuitively, a chain graph is a graph that looks like a
		 * linear chain link.
		 * Analogous to `undirected::makeChain`.= for DirectedGraph
		 * Here, a link consists of 3 vertices and 8 edges, with 1
		 * vertex being the "head" and 2 vertices the "tail". Edges
		 * exist from head to tail within a link, as well as from tail
		 * to the head of the next link. At the end is a single link with
		 * only a head vertex; this is not counted as part of the `length`
		 * links. For a more precise description, see the formal definition
		 * below.
		 * 
		 * Formal definition:
		 * G = (V, E) with
		 * V = {0, 1, 2, ..., 3 * length + 1}
		 * E = {(3i, 3i + 1)     | 0 <= i < length} U
		 *     {(3i + 1, 3i)     | 0 <= i < length} U
		 *     {(3i, 3i + 2)     | 0 <= i < length} U
		 *     {(3i + 2, 3i)     | 0 <= i < length} U
		 *     {(3i + 1, 3(i+1)) | 0 <= i < length} U
		 *     {(3(i+1), 3i + 1) | 0 <= i < length} U
		 * 	   {(3i + 2, 3(i+1)) | 0 <= i < length} U
		 * 	   {(3(i+1), 3i + 2) | 0 <= i < length}
		 */
		DirectedGraph<int> make2WayChain(std::size_t length, double w);

	}
#endif
}
#endif