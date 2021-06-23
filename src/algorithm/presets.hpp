#ifndef _FN_PRESETS
	#define _FN_PRESETS 0
	#include "../graph/graphw.hpp"
	#include "../graph/graphwb.hpp"

/*
 * Presets
 * The functions in this file construct predefined graphs.
 */
namespace firenoo::undirected {

	/*
	 * Constructs an undirected line graph with `n` vertices, with each
	 * edge having weight `w`. Vertices are labeled `0` to `n-1`.
	 */
	GraphWB<int> line(size_t n, double w);

	/*
	 * Constructs a complete graph with `n` vertices, with each
	 * edge having weight `w`.
	 */
	GraphWB<int> complete(size_t n, double w);

	/*
	 * Constructs a cycle graph with `n` vertices, with each
	 * edge having weight `w`.
	 */
	GraphWB<int> cycle(size_t n, double w);

	/*
	 * Constructs a lattice graph with `n*m` vertices, with each
	 * edge having weight `w`.
	 * Vertices are labeled `0` to `n*m-1`. 
	 */
	GraphWB<int> lattice(size_t n, size_t m, double w);

	/*
	 * Constructs a torus graph with `n x m` vertices, with each
	 * edge having weight `w`.
	 */
	GraphWB<int> torus(size_t n, size_t m, double w);

	/*
	 * Constructs a 3-cube graph. 8 vertices, 12 edges.
	 */
	GraphWB<int> cube3(double w);

	/*
	 * Constructs the Petersen graph. 10 vertices, 15 edges.
	 * Vertices are labeled 0-9.
	 * Edges have weight `w`.
	 */
	GraphWB<int> petersen(double w);

	/*
	 * Constructs the Chvátal graph. 12 vertices, 24 edges.
	 * Vertices are labeled 0-11.
	 * Edges have weight `w`.
	 */
	GraphWB<int> chavatal(double w);


	GraphWB<int> line(size_t n, double w) {
		GraphWB<int> g;
		for(int i = 0; i < n; ++i) {
			g.addVertex(i);
		}
		for(size_t i = 0; i < n-1; ++i) {
			g.addEdge(i, i+1, w);
		}
		return g;
	}

	GraphWB<int> complete(size_t n, double w) {
		GraphWB<int> g;
		for(int i = 0; i < n; ++i) {
			g.addVertex(i);
		}
		for(size_t i = 0; i < n-2; ++i) {
			for(size_t j = i+1; j < n-1; ++j) {
				g.addEdge(i, j, w);
			}
		}
		return g;
	}

	GraphWB<int> cycle(size_t n, double w) {
		GraphWB<int> g = line(n, w);
		g.addEdge(0, n-1, w);
		return g;
	}

	GraphWB<int> lattice(size_t n, size_t m, double w) {
		GraphWB<int> g ;
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

	GraphWB<int> torus(size_t n, size_t m, double w) {
		GraphWB<int> g = lattice(n, m, w);
		for(int i = 0; i < m; ++i) {
			//loop around - horizontal
			g.addEdge(i * n, (i + 1) * n - 1, w);
		}
		for(int i = 0; i < n; ++i) {
			//loop around - vertical
			g.addEdge(i, (m - 1) + i, w);
		}
	}

	GraphWB<int> cube3(double w) {
		GraphWB<int> g;
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

	GraphWB<int> petersen(double w) {
		GraphWB<int> g;
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
	
	GraphWB<int> chavatal(double w) {
		GraphWB<int> g;
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