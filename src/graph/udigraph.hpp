#ifndef _FN_GRAPHWB
    #define _FN_GRAPHWB 0
	#include "graph.hpp"
	#include "vertexwb.hpp"

namespace firenoo {

#define Vertex GraphVertexWB<T, W>
#define Graph Graph<T, W, Vertex, Hash, KeyEq>

/*
 * ----------------------------------------------------------------------------
 * UndirectedGraph
 * ----------------------------------------------------------------------------
 * Represents a weighted, undirected graph. Weights are represented by doubles
 * by default. The only difference between this class and GraphW is when
 * modifying an edge (u, v), the edge (v, u) is also modified. That is, the
 * following properties are guaranteed:
 * - (u, v) in E  <=> (v, u) in E
 * - w((u, v)) = w((v, u))
 * 
 * Template args:
 * T - type
 * W - weight type.
 * Hash - class that contains a hash function, see std::hash
 * KeyEq - class that contains eq function, see std::equal_to
 */
template<class T, class W = double, class Hash = std::hash<T>, class KeyEq = std::equal_to<T>>
class UndirectedGraph : public Graph {
public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	UndirectedGraph() : Graph() {}
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~UndirectedGraph() {
		Graph::clear();
	}

// WRITE operations -----------------------------------------------------------

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * Memory: A new GraphVertexW* object is allocated on heap.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - a pointer to the new vertex if it was created, or a pointer to the 
	 *    existing vertex.
	 */
	virtual Vertex* addVertex(const T& v) override {
		auto vertex = Graph::_vertices.find(v);
		if(vertex == Graph::_vertices.end()) {
			Vertex* vertex_new = new Vertex(v);
			Graph::_vertices[v] = vertex_new;
			return vertex_new;
		}
		return vertex->second;
	}

	/*
	 * Adds an undirected edge between the two specified vertices.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if if the edge was added.
	 *  - false if one of the conditions are true:
	 *     1. an edge already exists between the vertices, or
	 *     2. one or both vertices don't exist in the graph.
	 */
	virtual bool addEdge(const T& v1, const T& v2, W w) override {
		return Graph::addEdge(v1, v2, w) && Graph::addEdge(v2, v1, w);
	}


	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * 
	 * Memory: No memory is freed. It is safe to free the pointer returned.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 */
	virtual Vertex* removeVertex(const T& v) {
		auto search = Graph::_vertices.find(v);
		if(search == Graph::_vertices.end()) {
			return nullptr;
		}
		Vertex* vert = search->second;
		vert->clearEdges();
		Graph::_vertices.erase(search);
		return vert;
	}

};

#undef Vertex
#undef Graph

#define Vertex GraphVertexWB<int, W>
#define Graph Graph<int, W, Vertex, Hash, KeyEq>


/*
 * Int specialization
 */

/*
 * ----------------------------------------------------------------------------
 * UndirectedGraph
 * ----------------------------------------------------------------------------
 * Represents a weighted, undirected graph. Weights are represented by doubles
 * by default. The only difference between this class and GraphW is when
 * modifying an edge (u, v), the edge (v, u) is also modified. That is, the
 * following properties are guaranteed:
 * - (u, v) in E  <=> (v, u) in E
 * - w((u, v)) = w((v, u))
 * 
 * Template args:
 * T - type
 * W - weight type.
 * Hash - class that contains a hash function, see std::hash
 * KeyEq - class that contains eq function, see std::equal_to
 */
template<class W, class Hash, class KeyEq>
class UndirectedGraph<int, W, Hash, KeyEq> : public Graph {
public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	UndirectedGraph() : Graph() {}
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~UndirectedGraph() {
		Graph::clear();
	}

// WRITE operations -----------------------------------------------------------

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * Memory: A new GraphVertexW* object is allocated on heap.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - a pointer to the new vertex if it was created, or a pointer to the 
	 *    existing vertex.
	 */
	virtual Vertex* addVertex(const int& v) override {
		auto vertex = Graph::_vertices.find(v);
		if(vertex == Graph::_vertices.end()) {
			Vertex* vertex_new = new Vertex(v);
			Graph::_vertices[v] = vertex_new;
			return vertex_new;
		}
		return vertex->second;
	}

	/*
	 * Adds an undirected edge between the two specified vertices.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if if the edge was added.
	 *  - false if one of the conditions are true:
	 *     1. an edge already exists between the vertices, or
	 *     2. one or both vertices don't exist in the graph.
	 */
	virtual bool addEdge(const int& v1, const int& v2, W w) override {
		return Graph::addEdge(v1, v2, w);
	}


	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * 
	 * Memory: No memory is freed. It is safe to free the pointer returned.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 */
	virtual Vertex* removeVertex(const int& v) {
		auto search = Graph::_vertices.find(v);
		if(search == Graph::_vertices.end()) {
			return nullptr;
		}
		Vertex* vert = search->second;
		vert->clearEdges();
		Graph::_vertices.erase(search);
		return vert;
	}

};

#undef Vertex
#undef Graph
}

#endif