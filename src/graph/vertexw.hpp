#ifndef _FN_GRAPH_VERTEXW
    #define _FN_GRAPH_VERTEXW 0
	#include <unordered_map>
	#include <unordered_set>
	#include <iterator>
	#define Vertex GraphVertexW<T, W>
	#define VertexI GraphVertexW<int, W>
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
class GraphVertexW {	
private:
	const T& _obj;
	std::unordered_set<Vertex*> _indegrees;
	std::unordered_map<Vertex*, W> _neighbors;

public:

	GraphVertexW(const T& obj);

	GraphVertexW(const T&& obj);

	~GraphVertexW();

//READ operations	
	/*
	 * Gets the object associated to this vertex.
	 *
	 * READ operation.
	 * Parameters:
	 *  - None
	 * Returns:
	 *  - a const reference to the object.
	 */
	const T& get() const;

	/*
	 * Gets the outdegree of this vertex.
	 * READ operation.
	 * Returns:
	 * -- an unsigned int equal to the outdegree of this vertex.
	 */
	size_t outdegree() const;

	/*
	 * Gets the indegree of this vertex.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the indegree of this vertex.
	 */
	size_t indegree() const;

	/*
	 * Checks whether this vertex has an edge to the other vertex.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : Vertex to check.
	 * Returns:
	 *  - true if and only if there is an edge from this vertex to the other
	 *    vertex.
	 */
	bool hasEdge(Vertex* other) const;

	/*
	 * Gets the edge weight between the two vertices. Reads the value into 
	 * `in`.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : Vertex to check.
	 */
	void getEdge(Vertex* other, W& in) const;
	
//WRITE operations

	/*
	 * Adds an edge to the current graph.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - other  : the vertex the edge will point to
	 * Returns:
	 *  - true an edge was successfully added.
	 *  - false if an edge already exists.
	 */
	void addEdge(Vertex* other, W weight);
	
	/*
	 * Removes the specified edge.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - other : the other vertex that the edge points to
	 * Returns:
	 *  - true if and only if an edge was successfully removed.
	 */
	void removeEdge(Vertex* other);

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	void clearEdges();

	/*
	 * Removes all edges to this vertex.
	 *
	 * WRITE operation.
	 */
	void clearIndegree();

	/*
	 * Gets an iterator pointing to an arbitrary neighbor. 
	 */
	typename std::unordered_map<Vertex*, W>::const_iterator neighbors();

	/*
	 * Gets an iterator pointing to _neighbors.end(). 
	 */
	typename std::unordered_map<Vertex*, W>::const_iterator neighborsEnd();

};


//Constructors

template<class T, class W>
firenoo::GraphVertexW<T, W>::GraphVertexW(const T& obj) : _obj(obj) {}

template<class T, class W>
firenoo::GraphVertexW<T, W>::GraphVertexW(const T&& obj) : _obj(obj) {}

template<class T, class W>
firenoo::GraphVertexW<T, W>::~GraphVertexW() {
	clearEdges();
	clearIndegree();
}


//READ operations -------------------------------------------------------------

template<class T, class W>
void firenoo::GraphVertexW<T, W>::getEdge(Vertex* other, W& in) const {
	in = _neighbors.find(other)->second;
}

template<class T, class W>
const T& firenoo::GraphVertexW<T, W>::get() const {
	return _obj;
}

template<class T, class W>
size_t firenoo::GraphVertexW<T, W>::indegree() const {
	return _indegrees.size();
}

template<class T, class W>
size_t firenoo::GraphVertexW<T, W>::outdegree() const {
	return _neighbors.size();
}

template<class T, class W>
bool firenoo::GraphVertexW<T, W>::hasEdge(GraphVertexW<T, W>* other) const {
	auto edge = _neighbors.find(other);
	return edge != _neighbors.end();
}

//WRITE operations ------------------------------------------------------------

template<class T, class W>
void firenoo::GraphVertexW<T, W>::addEdge(GraphVertexW<T, W>* other, W weight) {
	//Lazy style - only add an entry if needed.
	_neighbors[other] = weight;
	other->_indegrees.insert(this);
}

template<class T, class W>
void firenoo::GraphVertexW<T, W>::removeEdge(GraphVertexW<T, W>* other) {
	_neighbors.erase(other);
	other->_indegrees.erase(this);
}

template<class T, class W>
void firenoo::GraphVertexW<T, W>::clearEdges() {
	for(auto neighbor : _neighbors) {
		neighbor.first->_indegrees.erase(this);
	}
	_neighbors.clear();

}


template<class T, class W>
void firenoo::GraphVertexW<T, W>::clearIndegree() {
	for(auto in_edge : _indegrees) {
		in_edge->_neighbors.erase(this);
	}
	_indegrees.clear();

}
#define ITERATOR typename std::unordered_map<GraphVertexW<T, W>*,W>::const_iterator

template<class T, class W>
ITERATOR firenoo::GraphVertexW<T, W>::neighbors() {
	return _neighbors.cbegin();
}

template<class T, class W>
ITERATOR firenoo::GraphVertexW<T, W>::neighborsEnd() {
	return _neighbors.cend();
}

#undef ITERATOR

/*
 * Template specialization 1: int
 * TODO: Can we reduce the amount of boilerplate code?
 */

template<class W>
class GraphVertexW<int, W> {	
private:
	//Holds the value instead of a reference
	const int _obj;
	std::unordered_set<GraphVertexW<int, W>*> _indegrees;
	std::unordered_map<GraphVertexW<int, W>*, W> _neighbors;

public:

	GraphVertexW(const int obj);

	~GraphVertexW();

//READ operations	
	/*
	 * Gets the object associated to this vertex.
	 *
	 * READ operation.
	 * Parameters:
	 *  - None
	 * Returns:
	 *  - a const reference to the object.
	 */
	const int get() const;

	/*
	 * Gets the outdegree of this vertex.
	 * READ operation.
	 * Returns:
	 * -- an unsigned int equal to the outdegree of this vertex.
	 */
	size_t outdegree() const;

	/*
	 * Gets the indegree of this vertex.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the indegree of this vertex.
	 */
	size_t indegree() const;

	/*
	 * Checks whether this vertex has an edge to the other vertex.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : Vertex to check.
	 * Returns:
	 *  - true if and only if there is an edge from this vertex to the other
	 *    vertex.
	 */
	bool hasEdge(GraphVertexW<int, W>* other) const;

	/*
	 * Gets the edge weight between the two vertices. Reads the value into 
	 * `in`.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : Vertex to check.
	 */
	void getEdge(GraphVertexW<int, W>* other, W& in) const;
	
//WRITE operations

	/*
	 * Adds an edge to the current graph.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - other  : the vertex the edge will point to
	 * Returns:
	 *  - true an edge was successfully added.
	 *  - false if an edge already exists.
	 */
	void addEdge(GraphVertexW<int, W>* other, W weight);
	
	/*
	 * Removes the specified edge.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - other : the other vertex that the edge points to
	 * Returns:
	 *  - true if and only if an edge was successfully removed.
	 */
	void removeEdge(GraphVertexW<int, W>* other);

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	void clearEdges();

	/*
	 * Removes all edges to this vertex.
	 *
	 * WRITE operation.
	 */
	void clearIndegree();

	/*
	 * Gets an iterator pointing to an arbitrary neighbor. 
	 */
	typename std::unordered_map<GraphVertexW<int, W>*, W>::const_iterator neighbors();

	/*
	 * Gets an iterator pointing to _neighbors.end(). 
	 */
	typename std::unordered_map<GraphVertexW<int, W>*, W>::const_iterator neighborsEnd();

};


//Constructors

template<class W>
firenoo::GraphVertexW<int, W>::GraphVertexW(const int obj) : _obj(obj) {}

template<class W>
firenoo::GraphVertexW<int, W>::~GraphVertexW() {
	clearEdges();
	clearIndegree();
}


//READ operations -------------------------------------------------------------

template<class W>
void firenoo::GraphVertexW<int, W>::getEdge(VertexI* other, W& in) const {
	in = _neighbors.find(other)->second;
}

template<class W>
const int firenoo::GraphVertexW<int, W>::get() const {
	return _obj;
}

template<class W>
size_t firenoo::GraphVertexW<int, W>::indegree() const {
	return _indegrees.size();
}

template<class W>
size_t firenoo::GraphVertexW<int, W>::outdegree() const {
	return _neighbors.size();
}

template<class W>
bool firenoo::GraphVertexW<int, W>::hasEdge(VertexI* other) const {
	auto edge = _neighbors.find(other);
	return edge != _neighbors.end();
}

//WRITE operations ------------------------------------------------------------

template<class W>
void firenoo::GraphVertexW<int, W>::addEdge(VertexI* other, W weight) {
	//Lazy style - only add an entry if needed.
	_neighbors[other] = weight;
	other->_indegrees.insert(this);
}

template<class W>
void firenoo::GraphVertexW<int, W>::removeEdge(VertexI* other) {
	_neighbors.erase(other);
	other->_indegrees.erase(this);
}

template<class W>
void firenoo::GraphVertexW<int, W>::clearEdges() {
	for(auto neighbor : _neighbors) {
		neighbor.first->_indegrees.erase(this);
	}
	_neighbors.clear();

}


template<class W>
void firenoo::GraphVertexW<int, W>::clearIndegree() {
	for(auto in_edge : _indegrees) {
		in_edge->_neighbors.erase(this);
	}
	_indegrees.clear();

}

#define ITERATOR typename std::unordered_map<GraphVertexW<int, W>*,W>::const_iterator

template<class W> 
ITERATOR firenoo::GraphVertexW<int, W>::neighbors() {
	return _neighbors.cbegin();
}

template<class W>
ITERATOR firenoo::GraphVertexW<int, W>::neighborsEnd() {
	return _neighbors.cend();
}

}
#undef Vertex
#undef VertexI
#undef ITERATOR
#endif

