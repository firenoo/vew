#ifndef _FN_GRAPHWB
    #define _FN_GRAPHWB 0
	#include "graph.hpp"
	#include "vertexwb.hpp"

namespace firenoo {
/*
 * ----------------------------------------------------------------------------
 * GraphWB
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
class GraphWB : Graph<T, W, GraphVertexWB<T, W>> {

private:

	std::unordered_map<T, GraphVertexWB<T, W>*, Hash, KeyEq> _vertices;
	size_t _edgeCount;
public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	GraphWB();
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~GraphWB();
	
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
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	virtual bool getEdge(const T& v1, const T& v2, W& in) const;

	/*
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	virtual bool getEdge(const T&& v1, const T& v2, W& in) const;

	/*
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	virtual bool getEdge(const T& v1, const T&& v2, W& in) const;

	/*
	 * Gets the edge weight between the two vertices. The weight is read into
	 * `in`.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  - in : variable to read the weight into
	 * Returns:
	 *  - true if and only if the edge exists
	 */
	virtual bool getEdge(const T&& v1, const T&& v2, W& in) const;

	/*
	 * Gets an iterator to an arbitrary vertex in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to some pairing (T, GraphVertexWB<T, W>*)
	 *    in this graph.
	 */
	virtual typename std::unordered_map<T, GraphVertexWB<T, W>*>::const_iterator begin() const;

	/*
	 * Gets the end iterator for the vertex set in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to the end iterator.
	 */
	virtual typename std::unordered_map<T, GraphVertexWB<T, W>*>::const_iterator end() const;

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
	virtual GraphVertexWB<T, W>* addVertex(const T& id);

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
	virtual GraphVertexWB<T, W>* addVertex(const T&& id);

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
	virtual bool addVertex(GraphVertexWB<T, W>* v);

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
	virtual GraphVertexWB<T, W>* removeVertex(const T& id);

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
	virtual GraphVertexWB<T, W>* removeVertex(const T&& id);

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
	virtual bool removeVertex(GraphVertexWB<T, W>* v);

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



};

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphWB<T, W, Hash, KeyEq>::GraphWB() : _edgeCount(0) {}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphWB<T, W, Hash, KeyEq>::~GraphWB() {
	clear();
}

//READ operations -------------------------------------------------------------

template<class T, class W, class Hash, class KeyEq>
size_t firenoo::GraphWB<T, W, Hash, KeyEq>::vertexCount() const {
	return _vertices.size();
}


template<class T, class W, class Hash, class KeyEq>
size_t firenoo::GraphWB<T, W, Hash, KeyEq>::edgeCount() const {
	return _edgeCount;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::hasVertex(const T& v) const {
	return _vertices.find(v) != _vertices.end();
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::hasVertex(const T&& v) const {
	return _vertices.find(v) != _vertices.end();
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::hasEdge(const T& v1, const T& v2) const {
	auto s1 = _vertices.find(v1);
	auto s2 = _vertices.find(v2);
	return s1 != _vertices.end() && 
	       s2 != _vertices.end() && 
		   s1->second->hasEdge(s2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::hasEdge(const T&& v1, const T& v2) const {
	auto s1 = _vertices.find(v1);
	auto s2 = _vertices.find(v2);
	return s1 != _vertices.end() && 
	       s2 != _vertices.end() && 
	       s1->second->hasEdge(s2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::hasEdge(const T& v1, const T&& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::hasEdge(const T&& v1, const T&& v2) const {
	auto vertex1 = _vertices.find(v1);
	auto vertex2 = _vertices.find(v2);
	return vertex1 != _vertices.end() && vertex2 != _vertices.end() && vertex1->second->hasEdge(vertex2->second);
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::getEdge(const T& v1, const T& v2, W& in) const {
	if(hasEdge(v1, v2)) {
		_vertices.find(v1)->second->getEdge(_vertices.find(v2)->second, in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::getEdge(const T&& v1, const T& v2, W& in) const {
	if(hasEdge(v1, v2)) {
		_vertices.find(v1)->second->getEdge(_vertices.find(v2)->second, in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::getEdge(const T& v1, const T&& v2, W& in) const {
	if(hasEdge(v1, v2)) {
		_vertices.find(v1)->second->getEdge(_vertices.find(v2)->second, in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::getEdge(const T&& v1, const T&& v2, W& in) const {
	if(hasEdge(v1, v2)) {
		_vertices.find(v1)->second->getEdge(_vertices.find(v2)->second, in);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
typename std::unordered_map<T, GraphVertexWB<T, W>*>::const_iterator firenoo::GraphWB<T, W, Hash, KeyEq>::begin() const{
	return _vertices.cbegin();
}

template<class T, class W, class Hash, class KeyEq>
typename std::unordered_map<T, GraphVertexWB<T, W>*>::const_iterator firenoo::GraphWB<T, W, Hash, KeyEq>::end() const {
	return _vertices.cend();
}

//WRITE operations ------------------------------------------------------------

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexWB<T, W>* firenoo::GraphWB<T, W, Hash, KeyEq>::addVertex(const T& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		firenoo::GraphVertexWB<T, W>* vertex_new = new firenoo::GraphVertexWB<T, W>(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexWB<T, W>* firenoo::GraphWB<T, W, Hash, KeyEq>::addVertex(const T&& v) {
	auto vertex = _vertices.find(v);
	if(vertex == _vertices.end()) {
		firenoo::GraphVertexWB<T, W>* vertex_new = new firenoo::GraphVertexWB<T, W>(v);
		_vertices[v] = vertex_new;
		return vertex_new;
	}
	return vertex->second;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::addVertex(GraphVertexWB<T, W>* v) {
	if(!hasVertex(v->get())) {
		_vertices[v->get()] = v;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexWB<T, W>* firenoo::GraphWB<T, W, Hash, KeyEq>::removeVertex(const T& v) {
	auto search = _vertices.find(v);
	if(search == _vertices.end()) {
		return nullptr;
	}
	search->second->clearEdges();
	_vertices.erase(search);
	return search->second;
}

template<class T, class W, class Hash, class KeyEq>
firenoo::GraphVertexWB<T, W>* firenoo::GraphWB<T, W, Hash, KeyEq>::removeVertex(const T&& v) {
	auto search = _vertices.find(v);
	if(search == _vertices.end()) {
		return nullptr;
	}
	search->second->clearEdges();
	_vertices.erase(search);
	return search->second;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::removeVertex(GraphVertexWB<T, W>* v) {
	auto search = _vertices.find(v->get());
	if(search != _vertices.end()) {
		search->second->clearEdges();
		_vertices.erase(search);
		delete search->second;
		return true;
	}
	return false;
}


template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::addEdge(const T& v1, const T& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexWB<T, W>* s1 = _vertices[v1];
		GraphVertexWB<T, W>* s2 = _vertices[v2];
		++_edgeCount;
		s1->addEdge(s2, w);
		s2->addEdge(s1, w);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::addEdge(const T&& v1, const T& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexWB<T, W>* s1 = _vertices[v1];
		GraphVertexWB<T, W>* s2 = _vertices[v2];
		++_edgeCount;
		s1->addEdge(s2, w);
		s2->addEdge(s1, w);
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::addEdge(const T& v1, const T&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexWB<T, W>* s1 = _vertices[v1];
		GraphVertexWB<T, W>* s2 = _vertices[v2];
		++_edgeCount;
		s1->addEdge(s2, w);
		s2->addEdge(s1, w);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::addEdge(const T&& v1, const T&& v2, W w) {
	if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
		GraphVertexWB<T, W>* s1 = _vertices[v1];
		GraphVertexWB<T, W>* s2 = _vertices[v2];
		++_edgeCount;
		s1->addEdge(s2, w);
		s2->addEdge(s1, w);
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::removeEdge(const T& v1, const T& v2) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->removeEdge(_vertices[v2]);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::removeEdge(const T&& v1, const T& v2) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->removeEdge(_vertices[v2]);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::removeEdge(const T& v1, const T&& v2) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->removeEdge(_vertices[v2]);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::removeEdge(const T&& v1, const T&& v2) {
	if(hasEdge(v1, v2)) {
		_vertices[v1]->removeEdge(_vertices[v2]);
		--_edgeCount;
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::removeNeighbors(const T& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		GraphVertexWB<T, W>* vertex = query->second;
		vertex->clearEdges();
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
bool firenoo::GraphWB<T, W, Hash, KeyEq>::removeNeighbors(const T&& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		GraphVertexWB<T, W>* vertex = query->second;
		_edgeCount -= vertex->outdegree();
		vertex->clearEdges();
		return true;
	}
	return false;
}

template<class T, class W, class Hash, class KeyEq>
void firenoo::GraphWB<T, W, Hash, KeyEq>::clear() {
	for(auto v : _vertices) {
		delete v.second;
	}
	_vertices.clear();
	_edgeCount = 0;
}

}

#endif