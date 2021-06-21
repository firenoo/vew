#ifndef _FN_GRAPHW
    #define FN_GRAPHW 0
	#include <unordered_map>
	#include <string>
	#include <functional>
	#include "vertexw.hpp"
	#include "graph.hpp"
/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

/*
 * ----------------------------------------------------------------------------
 * GraphW
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
class GraphW : public Graph<T, W, GraphVertexW<T, W>> {
private:
	std::unordered_map<std::reference_wrapper<const T>, GraphVertexW<T, W>*, Hash, KeyEq> _vertices;
	unsigned int _edgeCount;

public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	GraphW();
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~GraphW();
	
// Read operations ------------------------------------------------------------

	/*
	 * Gets the number of vertices in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - an unsigned integer representing the total number of vertices
	 *    stored in the graph.
	 */
	size_t vertexCount() const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	size_t edgeCount() const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	bool hasVertex(const T& v) const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	bool hasVertex(const T&& v) const;

	/*
	 * Checks whether an edge between two vertices exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex to check.
	 *  - v2 : sink vertex to check.
	 * Returns:
	 *  - true if and only if the edge (v1, v2) exists in this graph
	 */
	bool hasEdge(const T& v1, const T& v2) const;

	/*
	 * Checks whether an edge between two vertices exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex to check.
	 *  - v2 : sink vertex to check.
	 * Returns:
	 *  - true if and only if the edge (v1, v2) exists in this graph
	 */
	bool hasEdge(const T&& v1, const T& v2) const;

	/*
	 * Checks whether an edge between two vertices exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex to check.
	 *  - v2 : sink vertex to check.
	 * Returns:
	 *  - true if and only if the edge (v1, v2) exists in this graph
	 */
	bool hasEdge(const T& v1, const T&& v2) const;

	/*
	 * Checks whether an edge between two vertices exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex to check.
	 *  - v2 : sink vertex to check.
	 * Returns:
	 *  - true if and only if the edge (v1, v2) exists in this graph
	 */
	bool hasEdge(const T&& v1, const T&& v2) const;

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
	GraphVertexW<T, W>* addVertex(const T& id);

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
	GraphVertexW<T, W>* addVertex(const T&& id);

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
	bool addVertex(GraphVertexW<T, W>* v);

	/*
	 * Adds a directed edge between the two specified vertices.
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
	 *  - true if if the edge was added.
	 *  - false if one of the conditions are true:
	 *     1. an edge already exists between the vertices,
	 *     2. one or both vertices don't exist in the graph.
	 */
	bool addEdge(const T& v1, const T& v2, W w);

	/*
	 * Adds a directed edge between the two specified vertices.
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
	 *  - true if if the edge was added.
	 *  - false if one of the conditions are true:
	 *     1. an edge already exists between the vertices,
	 *     2. one or both vertices don't exist in the graph.
	 */
	bool addEdge(const T&& v1, const T& v2, W w);

	/*
	 * Adds a directed edge between the two specified vertices.
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
	 *  - true if if the edge was added.
	 *  - false if one of the conditions are true:
	 *     1. an edge already exists between the vertices,
	 *     2. one or both vertices don't exist in the graph.
	 */
	bool addEdge(const T& v1, const T&& v2, W w);

	/*
	 * Adds a directed edge between the two specified vertices.
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
	 *  - true if if the edge was added.
	 *  - false if one of the conditions are true:
	 *     1. an edge already exists between the vertices,
	 *     2. one or both vertices don't exist in the graph.
	 */
	bool addEdge(const T&& v1, const T&& v2, W w);

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
	GraphVertexW<T, W>* removeVertex(const T& id);

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
	GraphVertexW<T, W>* removeVertex(const T&& id);

	/*
	 * Removes the specified vertex from the graph. 
	 * 
	 * Memory: No memory is freed. It is safe to free the pointer passed in.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - true if and only if the vertex was removed.
	 */
	bool removeVertex(GraphVertexW<T, W>* v);

	/*
	 * Removes the specified edge from the graph.
	 *
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	bool removeEdge(const T& v1, const T& v2);

	/*
	 * Removes the specified edge from the graph.
	 *
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	bool removeEdge(const T&& v1, const T& v2);

	/*
	 * Removes the specified edge from the graph.
	 *
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	bool removeEdge(const T& v1, const T&& v2);

	/*
	 * Removes the specified edge from the graph.
	 *
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	bool removeEdge(const T&& v1, const T&& v2);

	/*
	 * Removes all edges from the specified vertex from the graph.
	 * Note about memory: no memory is deallocated.
	 * WRITE operation.
	 */
	bool removeNeighbors(const T& v);

	/*
	 * Removes all edges from the specified vertex from the graph.
	 * Note about memory: no memory is deallocated.
	 * WRITE operation.
	 */
	bool removeNeighbors(const T&& v);

	/*
	 * Removes all vertices and edges from the graph.
	 * Note about memory: All vertex pointers are deallocated via delete.
	 * WRITE operation. 
	 */
	void clear();

	/*
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	bool getEdge(const T& v1, const T& v2, W& in);

	/*
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	bool getEdge(const T&& v1, const T& v2, W& in);

	/*
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	bool getEdge(const T& v1, const T&& v2, W& in);

	/*
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	bool getEdge(const T&& v1, const T&& v2, W& in);

};

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphW<T, W, Hash, KeyEq>::GraphW() {
	this->_edgeCount = 0;
	
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphW<T, W, Hash, KeyEq>::~GraphW() {
	clear();
}

//READ operations -------------------------------------------------------------

template<class T, class W, class Hash, class KeyEq>
size_t firenoo::GraphW<T, W, Hash, KeyEq>::vertexCount() const {
	return _vertices.size();
}


template<class T, class W, class Hash, class KeyEq>
size_t firenoo::GraphW<T, W, Hash, KeyEq>::edgeCount() const {
	return this->_edgeCount;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::hasVertex(const T& v) const {
	return _vertices.find(v) != _vertices.end();
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::hasVertex(const T&& v) const {
	return _vertices.find(v) != _vertices.end();
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::hasEdge(const T& v1, const T& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::hasEdge(const T&& v1, const T& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::hasEdge(const T& v1, const T&& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::hasEdge(const T&& v1, const T&& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::getEdge(const T& v1, const T& v2, W& in) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::getEdge(const T&& v1, const T& v2, W& in) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::getEdge(const T& v1, const T&& v2, W& in) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::getEdge(const T&& v1, const T&& v2, W& in) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

//WRITE operations ------------------------------------------------------------

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::addVertex(const T& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		firenoo::GraphVertexW<T, W>* vertex_new = new firenoo::GraphVertexW<T, W>(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::addVertex(const T&& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		firenoo::GraphVertexW<T, W>* vertex_new = new firenoo::GraphVertexW<T, W>(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addVertex(GraphVertexW<T, W>* v) {
	if(!hasVertex(v->get())) {
		_vertices[v->get()] = v;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::removeVertex(const T& id) {
	auto v = _vertices.find(id);
	if(v == _vertices.end()) {
		return nullptr;
	}
	_vertices.erase(v);
	return v->second;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::removeVertex(const T&& id) {
	auto v = _vertices.find(id);
	if(v == _vertices.end()) {
		return nullptr;
	}
	_vertices.erase(v);
	return v->second;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeVertex(GraphVertexW<T, W>* v) {
	auto vertex = _vertices.find(v->get());
	if(vertex != _vertices.end()) {
		_vertices.erase(vertex);
		delete vertex->second;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T& v1, const T& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexW<T, W>* src = _vertices[v1];
		GraphVertexW<T, W>* snk = _vertices[v2];
		++_edgeCount;
		return src->addEdge(snk, w);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T&& v1, const T& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexW<T, W>* src = _vertices[v1];
		GraphVertexW<T, W>* snk = _vertices[v2];
		++_edgeCount;
		return src->addEdge(snk, w);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T& v1, const T&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexW<T, W>* src = _vertices[v1];
		GraphVertexW<T, W>* snk = _vertices[v2];
		++_edgeCount;
		return src->addEdge(snk, w);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T&& v1, const T&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexW<T, W>* src = _vertices[v1];
		GraphVertexW<T, W>* snk = _vertices[v2];
		++_edgeCount;
		return src->addEdge(snk, w);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T& v1, const T& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end()) {
		return src->second->removeEdge(snk->second);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T&& v1, const T& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end()) {
		return src->second->removeEdge(snk->second);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T& v1, const T&& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end()) {
		return src->second->removeEdge(snk->second);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T&& v1, const T&& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end()) {
		return src->second->removeEdge(snk->second);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeNeighbors(const T& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		GraphVertexW<T, W>* vertex = query->second;
		vertex->clearEdges();
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeNeighbors(const T&& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		GraphVertexW<T, W>* vertex = query->second;
		vertex->clearEdges();
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
void firenoo::GraphW<T, W, Hash, KeyEq>::clear() {
	for(auto v : _vertices) {
		delete v.second;
	}
	_vertices.clear();
}

}

#endif
