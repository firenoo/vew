#ifndef _FN_GRAPH_VERTEX
    #define _FN_GRAPH_VERTEX 0
	#include <unordered_map>
	#include <unordered_set>
	#include <iterator>
	#include <utility>
namespace firenoo {


/*
 * GraphVertex
 * This class attempts to reduce the amount of boilerplate code required.
 * It represents the most generic graph vertex, and is abstract.
 * T - backing type
 * W - weight type
 * V - vertex type to use in neighbor list
 */
template<class T, class W, class V>
class GraphVertex {
	template<class X, class Y>
	friend class GraphVertexW;
	template<class X, class Y>
	friend class GraphVertexWB;

protected:
	const T& _obj;
	std::unordered_map<V*, W> _neighbors;

public:

	GraphVertex(const T& obj) : _obj(obj) {}
	GraphVertex(const T&& obj) : _obj(std::move(obj)) {}
	virtual ~GraphVertex();

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
	virtual const T& get() const noexcept {
		return _obj;
	}

	/*
	 * Gets the indegree of this vertex.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the indegree of this vertex.
	 */
	virtual size_t indegree() const noexcept = 0;
	
	/*
	 * Gets the outdegree of this vertex.
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the outdegree of this vertex.
	 */
	virtual size_t outdegree() const noexcept {
		return _neighbors.size();
	}
	/*
	 * Gets the edge weight between the two vertices. Reads the value into 
	 * `in`.
	 * NO safety checking is performed.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : GraphVertex to check.
	 */
	virtual void getEdge(V* other, W& in) const {
		in = _neighbors[other];
	}

	/*
	 * Checks whether this vertex has an edge to the other vertex.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : GraphVertex to check.
	 * Returns:
	 *  - true if and only if there is an edge from this vertex to the other
	 *    vertex.
	 */
	virtual bool hasEdge(V* other) const noexcept {
		return _neighbors.find(other) != _neighbors.end();
	}
	
//WRITE operations

	/*
	 * Adds an edge to the current graph. This function will only
	 * add one edge `(this, other)` to the graph, with weight `weight`.
	 * NO safety checking is performed; at the end of this operation
	 * the edge should exist.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - other  : the vertex the edge will point to
	 */
	virtual void addEdge(V* other, W weight) {
		_neighbors[other] = weight;
	}
	
	/*
	 * Removes the edge (this, other) from the adjacency list.
	 * NO safety checking is performed; at the end of this operation
	 * the edge should not exist.
	 * WRITE operation.
	 * Parameters:
	 *  - other : the other vertex that the edge points to
	 */
	virtual void removeEdge(GraphVertex* other) {
		_neighbors.erase(other);
	}

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	virtual void clearEdges() {
		_neighbors.clear();
	}

	/*
	 * Gets an iterator pointing to an arbitrary neighbor. 
	 */
	virtual typename std::unordered_map<V*, W>::const_iterator neighbors() {
		return _neighbors.cbegin();
	}

	/*
	 * Gets an iterator pointing to _neighbors.end(). 
	 */
	virtual typename std::unordered_map<V*, W>::const_iterator neighborsEnd() {
		return _neighbors.cend();
	}

};

/*
 * GraphVertex (int specialization)
 * This class attempts to reduce the amount of boilerplate code required.
 * It represents the most generic graph vertex, and is abstract.
 * Instead of keeping references, it stores int data directly.
 * 
 */
template<class W, class V>
class GraphVertex<int, W, V> {	
protected:
	const int _obj;
	std::unordered_map<V*, W> _neighbors;
public:

	GraphVertex(const int& obj) : _obj(obj) {}
	GraphVertex(const int&& obj) : _obj(obj) {}
	virtual ~GraphVertex() {}

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
	virtual const int get() const noexcept {
		return _obj;
	}

	/*
	 * Gets the outdegree of this vertex.
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the outdegree of this vertex.
	 */
	virtual size_t outdegree() const noexcept {
		return _neighbors.size();
	}

	/*
	 * Gets the indegree of this vertex.
	 *
	 * READ operation.
	 * Returns:
	 *  - an unsigned int equal to the indegree of this vertex.
	 */
	virtual size_t indegree() const noexcept = 0;

	/*
	 * Checks whether this vertex has an edge to the other vertex.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : GraphVertex to check.
	 * Returns:
	 *  - true if and only if there is an edge from this vertex to the other
	 *    vertex.
	 */
	virtual bool hasEdge(V* other) const noexcept {
		return _neighbors.find(other) != _neighbors.end();
	}

	/*
	 * Gets the edge weight between the two vertices. Reads the value into 
	 * `in`.
	 * NO safety checking is performed.
	 *
	 * READ operation.
	 * Parameters:
	 *  - other : GraphVertex to check.
	 */
	virtual void getEdge(V* other, W& in) const {
		in = _neighbors.find(other)->second;
	}
	
//WRITE operations

	/*
	 * Adds an edge to the current graph. This function will only
	 * add one edge `(this, other)` to the graph, with weight `weight`.
	 * NO safety checking is performed; at the end of this operation
	 * the edge should exist.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - other  : the vertex the edge will point to
	 */
	virtual void addEdge(V* other, W weight) {
		_neighbors[other] = weight;
	}
	
	/*
	 * Removes the edge (this, other) from the adjacency list.
	 * NO safety checking is performed; at the end of this operation
	 * the edge should not exist.
	 * WRITE operation.
	 * Parameters:
	 *  - other : the other vertex that the edge points to
	 */
	virtual void removeEdge(V* other) {
		_neighbors.erase(other);
	}

	/*
	 * Removes all edges from this vertex.
	 *
	 * WRITE operation.
	 */
	virtual void clearEdges() {
		_neighbors.clear();
	}

	/*
	 * Gets an iterator pointing to an arbitrary neighbor. 
	 */
	virtual typename std::unordered_map<V*, W>::const_iterator neighbors() {
		return _neighbors.cbegin();
	}

	/*
	 * Gets an iterator pointing to _neighbors.end(). 
	 */
	virtual typename std::unordered_map<V*, W>::const_iterator neighborsEnd() {
		return _neighbors.cend();
	}

};

}
#endif