#ifndef _FN_GRAPH
    #define _FN_GRAPH 0

/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

/*
 * ---------------------------------------------------------------------------- 
 * Graph (Superclass)
 * ----------------------------------------------------------------------------
 * A representation of a mathematical graph object. Submembers of this class
 * are named with the following suffixes to indicate properties of each 
 * implementation.
 * 
 * Implementations should follow the behavior in the doucmentation. They can 
 * copy the docs here, but should include details such as memory allocation.
 * Any discrepency in behavior should be clearly documented.
 * 
 * Example: GraphU means that the graph implementation is unweighted, does not
 * multigraphs, and does not allow self-loops. In other words, it is a simple,
 * directed, unweighted graph.
 *  
 * The suffix order should respect the list below. 
 * 1. U / W - unweighted/weighted (must be one or the other)
 * 4. B - undirected (edges are bidirectional, optional)
 * 2. M - multigraph (multiple edges to the same vertex, optional)
 * 3. L - self-loops (edges from a vertex to itself, optional)
 * 
 * Template Args:
 * T - type of each vertex
 * W - type of weight.
 * V - type of vertex
 */
template<class T, class W, class V>
class Graph {

public:

	virtual ~Graph() {};

//READ operations

	/*
	 * Gets the number of vertices in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - an unsigned integer representing the total number of vertices
	 *    stored in the graph.
	 */
	virtual size_t vertexCount() const = 0;
	
	/*
	 * Gets the number of edges in this graph.
	 *
	 * READ operation.
	 * Returns:
	 *  - an integer representing the total number of edges in
	 *    the graph.
	 */
	virtual size_t edgeCount() const = 0;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const T& v) const = 0;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const T&& v) const = 0;

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
	virtual bool hasEdge(const T& v1, const T& v2) const = 0;
	
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
	virtual bool hasEdge(const T& v1, const T&& v2) const = 0;
	
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
	virtual bool hasEdge(const T&& v1, const T& v2) const = 0;
	
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
	virtual bool hasEdge(const T&& v1, const T&& v2) const = 0;

//WRITE operations

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - a pointer to the new vertex if it was created, or a pointer to the 
	 *    existing vertex.
	 */
	virtual V* addVertex(const T& v) = 0;

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - a pointer to the new vertex if it was created, or a pointer to the 
	 *    existing vertex.
	 */
	virtual V* addVertex(const T&& v) = 0;

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - true if and only if a vertex was added.
	 */
	virtual bool addVertex(V* v) = 0;

	/*
	 * Removes the specified vertex from the graph.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 */
	virtual V* removeVertex(const T& v) = 0;

	/*
	 * Removes the specified vertex from the graph. 
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 */
	virtual V* removeVertex(const T&& v) = 0;

	/*
	 * Removes the specified vertex from the graph. 
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - true if and only if the vertex was removed.
	 */
	virtual bool removeVertex(V* v) = 0;

	/*
	 * Adds a directed edge between the two specified vertices.
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
	virtual bool addEdge(const T& v1, const T& v2, W w) = 0;

	/*
	 * Adds a directed edge between the two specified vertices.
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
	virtual bool addEdge(const T&& v1, const T& v2, W w) = 0;

	/*
	 * Adds a directed edge between the two specified vertices.
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
	virtual bool addEdge(const T& v1, const T&& v2, W w) = 0;

	/*
	 * Adds a directed edge between the two specified vertices.
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
	virtual bool addEdge(const T&& v1, const T&& v2, W w) = 0;

	/*
	 * Removes the specified edge from the graph.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	virtual bool removeEdge(const T& v1, const T& v2) = 0;

	/*
	 * Removes the specified edge from the graph.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	virtual bool removeEdge(const T&& v1, const T& v2) = 0;

	/*
	 * Removes the specified edge from the graph.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	virtual bool removeEdge(const T& v1, const T&& v2) = 0;

	/*
	 * Removes the specified edge from the graph.
	 *
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 * Returns:
	 *  - true if and only if an edge was removed.
	 */
	virtual bool removeEdge(const T&& v1, const T&& v2) = 0;

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex 
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const T& v) = 0;

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const T&& v) = 0;

	/*
	 * Removes all vertices and edges from the graph.
	 * WRITE operation. 
	 */
	virtual void clear() = 0;
};



}

#endif
