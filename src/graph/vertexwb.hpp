#ifndef _FN_GRAPH_VERTEXWB
    #define _FN_GRAPH_VERTEXWB 0
	#include <unordered_map>
	#include <unordered_set>
	#include <iterator>
	#include "vertex.hpp"
namespace firenoo {
/*
 * ----------------------------------------------------------------------------
 * GraphVertexWB
 * ----------------------------------------------------------------------------
 * Representation of a graph vertex with weighted edges, specialized for
 * undirected use cases. For the most part, the code is the same, except there
 * is no need to keep track of indegrees (saves some memory).
 * Template args:
 * T - type of object that backs this vertex.
 * W - type to use as an edge weight. Must be comparable.
 * 
 * _indegree: Cached value of the indegree, updated lazily.
 * _obj: An identifier for the vertex.
 * _neighbors: Neighbors of this graph vertex.
 */
template<class T, class W>
class GraphVertexWB : public GraphVertex<T, W, GraphVertexWB<T, W>> {	
public:

	GraphVertexWB(const T& obj) : GraphVertex<T, W, GraphVertexWB>(obj) {}

	GraphVertexWB(const T&& obj) : GraphVertex<T, W, GraphVertexWB>(obj) {}

	~GraphVertexWB() {
		clearEdges();
	}

//READ operations	


	/*
	 * Gets the indegree of this vertex. Equal to the outdegree.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the outdegree of this vertex.
	 */
	size_t indegree() const noexcept {
		return GraphVertex<T,W,GraphVertexWB>::_neighbors.size();
	}

//WRITE operations


	void addEdge(GraphVertexWB* other, W weight) {
		GraphVertex<T, W, GraphVertexWB>::_neighbors[other] = weight;
		other->_neighbors[this] = weight;
	}

	/*
	 * Removes the edges (this, other) and (other, this) from the 
	 * adjacency list.
	 * NO safety checking is performed; at the end of this operation
	 * the edge should not exist.
	 * WRITE operation.
	 * Parameters:
	 *  - other : the other vertex that the edge points to
	 */
	void removeEdge(GraphVertexWB* other) {
		GraphVertex<T,W,GraphVertexWB>::_neighbors.erase(other);
		other->_neighbors.erase(this);
	}

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	void clearEdges() {
		for(auto neighbor : GraphVertex<T,W,GraphVertexWB>::_neighbors) {
			neighbor.first->_neighbors.erase(this);
		}
		GraphVertex<T,W,GraphVertexWB>::_neighbors.clear();
	}

};

/*
 * ----------------------------------------------------------------------------
 * GraphVertexWB (int specialization)
 * ----------------------------------------------------------------------------
 * Representation of a graph vertex with weighted edges, specialized for
 * undirected use cases. For the most part, the code is the same, except there
 * is no need to keep track of indegrees (saves some memory).
 * Template args:
 * T - type of object that backs this vertex.
 * W - type to use as an edge weight. Must be comparable.
 * 
 * _indegree: Cached value of the indegree, updated lazily.
 * _obj: An identifier for the vertex.
 * _neighbors: Neighbors of this graph vertex.
 */
template<class W>
class GraphVertexWB<int, W> : public GraphVertex<int, W, GraphVertexWB<int, W>> {	
public:

	GraphVertexWB(const int& obj) : GraphVertex<int, W, GraphVertexWB>(obj) {}

	GraphVertexWB(const int&& obj) : GraphVertex<int, W, GraphVertexWB>(obj) {}

	~GraphVertexWB() {
		clearEdges();
	}

//READ operations	


	/*
	 * Gets the indegree of this vertex. Equal to the outdegree.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the outdegree of this vertex.
	 */
	size_t indegree() const noexcept {
		return GraphVertex<int,W,GraphVertexWB>::_neighbors.size();
	}

//WRITE operations


	void addEdge(GraphVertexWB* other, W weight) {
		GraphVertex<int, W, GraphVertexWB>::_neighbors[other] = weight;
		other->_neighbors[this] = weight;
	}

	/*
	 * Removes the edges (this, other) and (other, this) from the 
	 * adjacency list.
	 * NO safety checking is performed; at the end of this operation
	 * the edge should not exist.
	 * WRITE operation.
	 * Parameters:
	 *  - other : the other vertex that the edge points to
	 */
	void removeEdge(GraphVertexWB* other) {
		GraphVertex<int,W,GraphVertexWB>::_neighbors.erase(other);
		other->_neighbors.erase(this);
	}

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	void clearEdges() {
		for(auto neighbor : GraphVertex<int,W,GraphVertexWB>::_neighbors) {
			neighbor.first->_neighbors.erase(this);
		}
		GraphVertex<int,W,GraphVertexWB>::_neighbors.clear();
	}

};

}
#endif

