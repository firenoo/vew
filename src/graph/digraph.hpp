#ifndef _FN_GRAPHW
    #define _FN_GRAPHW 0
	#include "vertexw.hpp"
	#include "graph.hpp"
/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

#define Vertex GraphVertexW<T, W>
#define Graph Graph<T, W, Vertex, Hash, KeyEq>
/*
 * ----------------------------------------------------------------------------
 * DirectedGraph
 * ----------------------------------------------------------------------------
 * Represents a weighted, directed graph. Weights are represented by doubles by
 * default.
 * 
 * Template args:
 * T - type
 * W - weight type.
 * Hash - class that contains a hash function, see std::hash
 * KeyEq - class that contains eq function, see std::equal_to
 */
template<class T, class W = double, class Hash = std::hash<T>, class KeyEq = std::equal_to<T>>
class DirectedGraph : public Graph {

public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	DirectedGraph() : Graph() {}
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~DirectedGraph() {
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
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T& v1, const T& v2, W w) {
		return Graph::addEdge(v1, v2, w) && Graph::addEdge(v2, v1, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T& v1, const T&& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T&& v1, const T& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T&& v1, const T&& v2, W w) {
		return addBiEdge(v1, v2, w);
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
	virtual Vertex* removeVertex(const T& v) override {
		Vertex* vert = Graph::removeVertex(v);
		vert->clearIndegree();
		return vert;
	}
};

#undef Vertex
#undef Graph
#define Vertex GraphVertexW<int, W>
#define Graph Graph<int, W, Vertex, Hash, KeyEq>
/*
 * ----------------------------------------------------------------------------
 * DirectedGraph (int)
 * ----------------------------------------------------------------------------
 * Represents a weighted, directed graph. Weights are represented by doubles by
 * default.
 * 
 * Template args:
 * T - type
 * W - weight type.
 * Hash - class that contains a hash function, see std::hash
 * KeyEq - class that contains eq function, see std::equal_to
 */
template<class W, class Hash, class KeyEq>
class DirectedGraph<int, W, Hash, KeyEq> : public Graph {

public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	DirectedGraph() : Graph() {}
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~DirectedGraph() {
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
	 * Adds the vertex to the graph if it doesn't exist already.
	 *
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - true if and only if a vertex was added.
	 */
	virtual bool addVertex(Vertex* v) override {
		if(!Graph::hasVertex(v->get())) {
			Graph::_vertices[v->get()] = v;
			return true;
		}
		return false;
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int& v1, const int& v2, W w) {
		return Graph::addEdge(v1, v2, w) && Graph::addEdge(v2, v1, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int& v1, const int&& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int&& v1, const int& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int&& v1, const int&& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	virtual Vertex* removeVertex(const int& v) override {
		Vertex* vert = Graph::removeVertex(v);
		vert->clearIndegree();
		return vert;
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
	virtual bool removeVertex(Vertex* v) override {
		if(Graph::removeVertex(v)) {
			v->clearIndegree();
			return true;
		}
		return false;;
	}
};
#undef Vertex
#undef Graph
}

#endif
