#ifndef _FN_GRAPH_VERTEXWB
    #define _FN_GRAPH_VERTEXWB 0
	#include <unordered_map>
	#include <unordered_set>
	#include <iterator>
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
class GraphVertexWB {	
private:
	const T& _obj;
	std::unordered_map<GraphVertexWB<T, W>*, W> _neighbors;

public:

	GraphVertexWB(const T& obj);

	GraphVertexWB(const T&& obj);

	~GraphVertexWB();

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
	 * Gets the outdegree of this vertex. Equal to the indegree.
	 * READ operation.
	 * Returns:
	 * -- an unsigned int equal to the outdegree of this vertex.
	 */
	size_t outdegree() const;

	/*
	 * Gets the indegree of this vertex. Equal to the outdegree.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the outdegree of this vertex.
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
	bool hasEdge(GraphVertexWB<T, W>* other) const;

	/*
	 * Gets the edge weight between the two vertices. Reads the value into 
	 * `in`.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : Vertex to check.
	 */
	void getEdge(GraphVertexWB<T, W>* other, W& in) const;

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
	bool addEdge(GraphVertexWB<T, W>* other, W weight);
	
	/*
	 * Removes the specified edge.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - other : the other vertex that the edge points to
	 * Returns:
	 *  - true if and only if an edge was successfully removed.
	 */
	bool removeEdge(GraphVertexWB<T, W>* other);

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	void clearEdges();

	/*
	 * Gets an iterator pointing to an arbitrary neighbor. 
	 */
	typename std::unordered_map<GraphVertexWB<T, W>*, W>::const_iterator neighbors();

	/*
	 * Gets an iterator pointing to _neighbors.end(). 
	 */
	typename std::unordered_map<GraphVertexWB<T, W>*, W>::const_iterator neighborsEnd();

};


//Constructors

template<class T, class W>
firenoo::GraphVertexWB<T, W>::GraphVertexWB(const T& obj) : _obj(obj) {}

template<class T, class W>
firenoo::GraphVertexWB<T, W>::GraphVertexWB(const T&& obj) : _obj(obj) {}

template<class T, class W>
firenoo::GraphVertexWB<T, W>::~GraphVertexWB() {
	clearEdges();
}


//READ operations -------------------------------------------------------------

template<class T, class W>
void firenoo::GraphVertexWB<T, W>::getEdge(GraphVertexWB<T,W>* other, W& in) const {
	in = _neighbors.find(other)->second;
}

template<class T, class W>
const T& firenoo::GraphVertexWB<T, W>::get() const {
	return _obj;
}

template<class T, class W>
size_t firenoo::GraphVertexWB<T, W>::indegree() const {
	return _neighbors.size();
}

template<class T, class W>
size_t firenoo::GraphVertexWB<T, W>::outdegree() const {
	return _neighbors.size();
}

template<class T, class W>
bool firenoo::GraphVertexWB<T, W>::hasEdge(GraphVertexWB<T, W>* other) const {
	auto edge = _neighbors.find(other);
	return edge != _neighbors.end();
}

//WRITE operations ------------------------------------------------------------

template<class T, class W>
bool firenoo::GraphVertexWB<T, W>::addEdge(GraphVertexWB<T, W>* other, W weight) {
	//Lazy style - only add an entry if needed.
	if(!hasEdge(other)) {
		_neighbors[other] = weight;
		other->_neighbors[this] = weight;
		return true;
	}
	return false;
}

template<class T, class W>
bool firenoo::GraphVertexWB<T, W>::removeEdge(GraphVertexWB<T, W>* other) {
	if(hasEdge(other)) {
		_neighbors.erase(other);
		other->_neighbors.erase(this);
		return true;
	}
	return false;
}

template<class T, class W>
void firenoo::GraphVertexWB<T, W>::clearEdges() {
	for(auto neighbor : _neighbors) {
		neighbor.first->_neighbors.erase(this);
	}
	_neighbors.clear();
}

template<class T, class W>
typename std::unordered_map<GraphVertexWB<T, W>*,W>::const_iterator firenoo::GraphVertexWB<T, W>::neighbors() {
	return _neighbors.cbegin();
}

template<class T, class W>
typename std::unordered_map<GraphVertexWB<T, W>*,W>::const_iterator firenoo::GraphVertexWB<T, W>::neighborsEnd() {
	return _neighbors.cend();
}

}
#endif

