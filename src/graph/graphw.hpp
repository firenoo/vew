#ifndef _FN_GRAPHW
    #define _FN_GRAPHW 0
	#include <functional>
	#include <unordered_map>
	#include <string>
	#include "vertexw.hpp"
	#include "graph.hpp"
/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

#define Vertex GraphVertexW<T, W>
#define VertexI GraphVertexW<int, W>
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
class GraphW : public Graph<T, W, Vertex> {
private:
	std::unordered_map<std::reference_wrapper<const T>, Vertex*, Hash, KeyEq> _vertices;
	size_t _edgeCount;

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
	virtual size_t vertexCount() const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual size_t edgeCount() const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const T& v) const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const T&& v) const;

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
	virtual bool hasEdge(const T& v1, const T& v2) const;

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
	virtual bool hasEdge(const T&& v1, const T& v2) const;

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
	virtual bool hasEdge(const T& v1, const T&& v2) const;

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
	virtual bool hasEdge(const T&& v1, const T&& v2) const;

	/*
	 * Gets an iterator to an arbitrary vertex in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to some pairing (T, GraphVertexW<T, W>*)
	 *    in this graph.
	 */
	virtual typename std::unordered_map<T, Vertex*>::const_iterator begin() const;

	/*
	 * Gets the end iterator for the vertex set in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to the end iterator.
	 */
	virtual typename std::unordered_map<T, Vertex*>::const_iterator end() const;

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
	virtual GraphVertexW<T, W>* addVertex(const T& v);

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
	virtual GraphVertexW<T, W>* addVertex(const T&& v);

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
	virtual bool addVertex(Vertex* v);

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
	virtual bool addEdge(const T& v1, const T& v2, W w);

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
	virtual bool addEdge(const T&& v1, const T& v2, W w);

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
	virtual bool addEdge(const T& v1, const T&& v2, W w);

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
	virtual bool addEdge(const T&& v1, const T&& v2, W w);

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
	virtual GraphVertexW<T, W>* removeVertex(const T& v);

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
	virtual GraphVertexW<T, W>* removeVertex(const T&& v);

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
	virtual bool removeVertex(Vertex* v);

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
	virtual bool removeEdge(const T& v1, const T& v2);

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
	virtual bool removeEdge(const T&& v1, const T& v2);

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
	virtual bool removeEdge(const T& v1, const T&& v2);

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
	virtual bool removeEdge(const T&& v1, const T&& v2);

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex 
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const T& v);

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex 
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const T&& v);

	/*
	 * Removes all vertices and edges from the graph.
	 * Note about memory: All vertex pointers are deallocated via delete.
	 * WRITE operation. 
	 */
	virtual void clear();

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
	virtual bool getEdge(const T& v1, const T& v2, W& in);

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
	virtual bool getEdge(const T&& v1, const T& v2, W& in);

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
	virtual bool getEdge(const T& v1, const T&& v2, W& in);

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
	virtual bool getEdge(const T&& v1, const T&& v2, W& in);

};

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphW<T, W, Hash, KeyEq>::GraphW() : _edgeCount(0) {}

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
		//Read into `in`
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::getEdge(const T&& v1, const T&& v2, W& in) {
	if(hasEdge(v1, v2)) {
		//Read into `in`
		Vertex* src = _vertices[v1];
		Vertex* snk = _vertices[v2];
		src->getEdge(snk, in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
typename std::unordered_map<T, Vertex*>::const_iterator firenoo::GraphW<T, W, Hash, KeyEq>::begin() const {
	return _vertices.cbegin();
}

template<class T, class W, class Hash, class KeyEq>
typename std::unordered_map<T, Vertex*>::const_iterator firenoo::GraphW<T, W, Hash, KeyEq>::end() const {
	return _vertices.cend();
}

//WRITE operations ------------------------------------------------------------

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::addVertex(const T& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		Vertex* vertex_new = new Vertex(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::addVertex(const T&& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		Vertex* vertex_new = Vertex(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addVertex(Vertex* v) {
	if(!hasVertex(v->get())) {
		_vertices[v->get()] = v;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::removeVertex(const T& v) {
	auto search = _vertices.find(v);
	if(search == _vertices.end()) {
		return nullptr;
	}
	search->second->clearIndegree();
	_vertices.erase(search);
	return search->second;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexW<T, W>* firenoo::GraphW<T, W, Hash, KeyEq>::removeVertex(const T&& v) {
	auto search = _vertices.find(v);
	if(search == _vertices.end()) {
		return nullptr;
	}
	search->second->clearIndegree();
	_vertices.erase(search);
	return search->second;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeVertex(Vertex* v) {
	auto search = _vertices.find(v->get());
	if(search != _vertices.end()) {
		search->second->clearIndegree();
		_vertices.erase(search);
		delete search->second;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T& v1, const T& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		Vertex* src = _vertices[v1];
		Vertex* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T&& v1, const T& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		Vertex* src = _vertices[v1];
		Vertex* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T& v1, const T&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		Vertex* src = _vertices[v1];
		Vertex* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::addEdge(const T&& v1, const T&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		Vertex* src = _vertices[v1];
		Vertex* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T& v1, const T& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T&& v1, const T& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T& v1, const T&& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeEdge(const T&& v1, const T&& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeNeighbors(const T& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		Vertex* vertex = query->second;
		_edgeCount -= vertex->outdegree();
		vertex->clearEdges();
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphW<T, W, Hash, KeyEq>::removeNeighbors(const T&& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		Vertex* vertex = query->second;
		_edgeCount -= vertex->outdegree();
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
	_edgeCount = 0;
}

/*
 * ----------------------------------------------------------------------------
 * GraphW (int)
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
template<class W>
class GraphW<int, W> : public Graph<int, W, VertexI> {
private:
	std::unordered_map<int, VertexI*> _vertices;
	size_t _edgeCount;

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
	virtual size_t vertexCount() const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual size_t edgeCount() const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const int& v) const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const int&& v) const;

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
	virtual bool hasEdge(const int& v1, const int& v2) const;

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
	virtual bool hasEdge(const int&& v1, const int& v2) const;

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
	virtual bool hasEdge(const int& v1, const int&& v2) const;

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
	virtual bool hasEdge(const int&& v1, const int&& v2) const;

	/*
	 * Gets an iterator to an arbitrary vertex in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to some pairing (T, GraphVertexW<T, W>*)
	 *    in this graph.
	 */
	virtual typename std::unordered_map<int, VertexI*>::const_iterator begin() const;

	/*
	 * Gets the end iterator for the vertex set in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to the end iterator.
	 */
	virtual typename std::unordered_map<int, VertexI*>::const_iterator end() const;

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
	virtual GraphVertexW<int, W>* addVertex(const int& v);

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
	virtual GraphVertexW<int, W>* addVertex(const int&& v);

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
	virtual bool addVertex(VertexI* v);

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
	virtual bool addEdge(const int& v1, const int& v2, W w);

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
	virtual bool addEdge(const int&& v1, const int& v2, W w);

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
	virtual bool addEdge(const int& v1, const int&& v2, W w);

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
	virtual bool addEdge(const int&& v1, const int&& v2, W w);

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
	virtual GraphVertexW<int, W>* removeVertex(const int& v);

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
	virtual GraphVertexW<int, W>* removeVertex(const int&& v);

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
	virtual bool removeVertex(VertexI* v);

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
	virtual bool removeEdge(const int& v1, const int& v2);

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
	virtual bool removeEdge(const int&& v1, const int& v2);

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
	virtual bool removeEdge(const int& v1, const int&& v2);

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
	virtual bool removeEdge(const int&& v1, const int&& v2);

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex 
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const int& v);

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex 
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const int&& v);

	/*
	 * Removes all vertices and edges from the graph.
	 * Note about memory: All vertex pointers are deallocated via delete.
	 * WRITE operation. 
	 */
	virtual void clear();

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
	virtual bool getEdge(const int& v1, const int& v2, W& in);

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
	virtual bool getEdge(const int&& v1, const int& v2, W& in);

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
	virtual bool getEdge(const int& v1, const int&& v2, W& in);

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
	virtual bool getEdge(const int&& v1, const int&& v2, W& in);

};

template<class W>
firenoo::GraphW<int, W>::GraphW() : _edgeCount(0) {}

template<class W>
firenoo::GraphW<int, W>::~GraphW() {
	clear();
}

//READ operations -------------------------------------------------------------

template<class W>
size_t firenoo::GraphW<int, W>::vertexCount() const {
	return _vertices.size();
}


template<class W>
size_t firenoo::GraphW<int, W>::edgeCount() const {
	return this->_edgeCount;
}

template<class W>
bool firenoo::GraphW<int, W>::hasVertex(const int& v) const {
	return _vertices.find(v) != _vertices.end();
}

template<class W>
bool firenoo::GraphW<int, W>::hasVertex(const int&& v) const {
	return _vertices.find(v) != _vertices.end();
}

template<class W>
bool firenoo::GraphW<int, W>::hasEdge(const int& v1, const int& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class W>
bool firenoo::GraphW<int, W>::hasEdge(const int&& v1, const int& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class W>
bool firenoo::GraphW<int, W>::hasEdge(const int& v1, const int&& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class W>
bool firenoo::GraphW<int, W>::hasEdge(const int&& v1, const int&& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class W>
bool firenoo::GraphW<int, W>::getEdge(const int& v1, const int& v2, W& in) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::getEdge(const int&& v1, const int& v2, W& in) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::getEdge(const int& v1, const int&& v2, W& in) {
	if(hasEdge(v1, v2)) {
		//Read into `in`
		_vertices[v1]->getEdge(_vertices[v2], in);
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::getEdge(const int&& v1, const int&& v2, W& in) {
	if(hasEdge(v1, v2)) {
		//Read into `in`
		VertexI* src = _vertices[v1];
		VertexI* snk = _vertices[v2];
		src->getEdge(snk, in);
		return true;
	}
	return false;
}

#define ITERATOR typename std::unordered_map<int, VertexI*>::const_iterator

template<class W> 
ITERATOR firenoo::GraphW<int, W>::begin() const {
	return _vertices.cbegin();
}

template<class W>
ITERATOR firenoo::GraphW<int, W>::end() const {
	return _vertices.cend();
}
//WRITE operations ------------------------------------------------------------

template<class W>
firenoo::GraphVertexW<int, W>* firenoo::GraphW<int, W>::addVertex(const int& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		firenoo::GraphVertexW<int, W>* vertex_new = new VertexI(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class W>
firenoo::GraphVertexW<int, W>* firenoo::GraphW<int, W>::addVertex(const int&& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		VertexI* vertex_new = new VertexI(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class W>
bool firenoo::GraphW<int, W>::addVertex(VertexI* v) {
	if(!hasVertex(v->get())) {
		_vertices[v->get()] = v;
		return true;
	}
	return false;
}

template<class W>
firenoo::GraphVertexW<int, W>* firenoo::GraphW<int, W>::removeVertex(const int& v) {
	auto search = _vertices.find(v);
	if(search == _vertices.end()) {
		return nullptr;
	}
	search->second->clearIndegree();
	_vertices.erase(search);
	return search->second;
}

template<class W>
firenoo::GraphVertexW<int, W>* firenoo::GraphW<int, W>::removeVertex(const int&& v) {
	auto search = _vertices.find(v);
	if(search == _vertices.end()) {
		return nullptr;
	}
	search->second->clearIndegree();
	_vertices.erase(search);
	return search->second;
}

template<class W>
bool firenoo::GraphW<int, W>::removeVertex(VertexI* v) {
	auto search = _vertices.find(v->get());
	if(search != _vertices.end()) {
		search->second->clearIndegree();
		_vertices.erase(search);
		delete search->second;
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::addEdge(const int& v1, const int& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		VertexI* src = _vertices[v1];
		VertexI* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::addEdge(const int&& v1, const int& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		VertexI* src = _vertices[v1];
		VertexI* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::addEdge(const int& v1, const int&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		VertexI* src = _vertices[v1];
		VertexI* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::addEdge(const int&& v1, const int&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		VertexI* src = _vertices[v1];
		VertexI* snk = _vertices[v2];
		++_edgeCount;
		src->addEdge(snk, w);
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::removeEdge(const int& v1, const int& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::removeEdge(const int&& v1, const int& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::removeEdge(const int& v1, const int&& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::removeEdge(const int&& v1, const int&& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
		src->second->removeEdge(snk->second);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::removeNeighbors(const int& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		VertexI* vertex = query->second;
		_edgeCount -= vertex->outdegree();
		vertex->clearEdges();
		return true;
	}
	return false;
}

template<class W>
bool firenoo::GraphW<int, W>::removeNeighbors(const int&& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		VertexI* vertex = query->second;
		_edgeCount -= vertex->outdegree();
		vertex->clearEdges();
		return true;
	}
	return false;
}

template<class W>
void firenoo::GraphW<int, W>::clear() {
	for(auto v : _vertices) {
		delete v.second;
	}
	_vertices.clear();
	_edgeCount = 0;
}
#undef ITERATOR


#undef Vertex
#undef VertexI
}

#endif
