#ifndef _FN_GRAPH_VERTEXW
    #define _FN_GRAPH_VERTEXW 0
	#include <unordered_map>
	#include <unordered_set>
	#include <iterator>
	#include "vertex.hpp"
namespace firenoo {
/*
 * ----------------------------------------------------------------------------
 * GraphVertexW
 * ----------------------------------------------------------------------------
 * Representation of a general graph vertex with weighted edges.
 * Template args:
 * T - type of object that backs this vertex.
 * W - type to use as an edge weight. Must be comparable.
 * 
 * _indegree: Cached value of the indegree, updated lazily.
 * _obj: An identifier for the vertex.
 * _neighbors: Neighbors of this graph vertex.
 */

template<class T, class W>
class GraphVertexW : public GraphVertex<T, W, GraphVertexW<T,W>> {	
private:
	std::unordered_set<GraphVertexW*> _indegrees;

public:
//Declarations

//Implementations
	GraphVertexW(const T& obj) : GraphVertex<T, W, GraphVertexW>(obj) {}

	GraphVertexW(const T&& obj) : GraphVertex<T, W, GraphVertexW>(obj) {}

	~GraphVertexW() {
		clearEdges();
		clearIndegree();
	}

//READ operations	

	/*
	 * Gets the indegree of this vertex.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the indegree of this vertex.
	 */
	size_t indegree() const noexcept {
		return _indegrees.size();
	}

//WRITE operations



	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	void clearEdges() {
		for(auto neighbor : GraphVertex<T,W,GraphVertexW>::_neighbors) {
			neighbor.first->_neighbors.erase(this);
		}
		GraphVertex<T,W,GraphVertexW>::_neighbors.clear();

	}

	/*
	 * Removes all edges to this vertex.
	 *
	 * WRITE operation.
	 */
	void clearIndegree() {
		for(auto in_edge : _indegrees) {
			in_edge->_neighbors.erase(this);
		}
		_indegrees.clear();
	}

};

/*
 * Template specialization 1: int
 */
template<class W>
class GraphVertexW<int, W> : public GraphVertex<int, W, GraphVertexW<int, W>> {	
private:
	std::unordered_set<GraphVertexW*> _indegrees;

public:

	GraphVertexW(const int& obj) : GraphVertex<int, W, GraphVertexW>(obj) {}

	GraphVertexW(const int&& obj) : GraphVertex<int, W, GraphVertexW>(std::move(obj)) {}

	~GraphVertexW() {
		clearEdges();
		clearIndegree();
	}

//READ operations	

	/*
	 * Gets the indegree of this vertex.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the indegree of this vertex.
	 */
	size_t indegree() const noexcept {
		return _indegrees.size();
	}

//WRITE operations

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	void clearEdges() {
		for(auto neighbor : GraphVertex<int,W,GraphVertexW>::_neighbors) {
			neighbor.first->_neighbors.erase(this);
		}
		GraphVertex<int,W,GraphVertexW>::_neighbors.clear();

	}

	/*
	 * Removes all edges to this vertex.
	 *
	 * WRITE operation.
	 */
	void clearIndegree() {
		for(auto in_edge : _indegrees) {
			in_edge->_neighbors.erase(this);
		}
		_indegrees.clear();
	}

};

}
#endif

