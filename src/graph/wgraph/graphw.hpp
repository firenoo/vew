#ifndef _FN_GRAPHW
    #define FN_GRAPHW 0
	#include <unordered_map>
	#include <string>
	#include "graph_vertex.hpp"
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
 * This class is intended to represent graphs with vertices that can contain no
 * more than one edge to any vertex. Edges are weighted, and self-loops are
 * allowed. Edge weights are represented with doubles.
 * 
 * Template arg:
 * T - type
 * 
 */
template<class T>
class GraphW : public Graph<T, double, GraphVertex<T>> {
private:
	std::unordered_map<T&, GraphVertex<T>*> _vertices;
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
	 * Returns:
	 * -- an unsigned integer representing the total number of vertices
	 *    stored in the graph.
	 * READ operation.
	 */
	unsigned int vertexCount() const;

	/*
	 * Gets the number of edges in this graph.
	 * Returns:
	 * -- an unsigned integer representing the total number of edges in
	 *    the graph.
	 * READ operation.
	 */
	unsigned int edgeCount() const;

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * Parameters:
	 * -- (V&) v : vertex value to be check.
	 * Returns:
	 * -- true if and only if the vertex object exists in this graph
	 */
	bool hasVertex(const T& v) const;

	/*
	 * Checks whether an edge between two vertices exists in the graph.
	 * Parameters:
	 * -- (V&) v1 : source vertex value to check.
	 * -- (V&) v2 : sink vertex value to check.
	 * Returns:
	 * -- true if and only if the vertex object exists in this graph
	 */
	bool hasEdge(const T& v1, const T& v2) const;

// WRITE operations -----------------------------------------------------------

	/*
	 * Adds the specified object as a vertex to the graph. If the object already
	 * exists, this method does nothing and returns false.
	 * Parameters:
	 * -- (T&) id : name of the vertex.
	 * Returns:
	 * -- a pointer to the vertex if it was created, or nullptr if operation
	 *    failed.
	 * WRITE operation.
	 */
	GraphVertex<T>* addVertex(const T& id);

	/*
	 * Adds the vertex to the graph. If the object already
	 * exists, this method does nothing and returns false.
	 * Parameters:
	 * -- (GraphVertex*) id : name of the vertex.
	 * Returns:
	 * -- True iff the vertex was added.
	 * WRITE operation.
	 */
	bool addVertex(const GraphVertex<T>* v);

	/*
	 * Adds a directed edge between the two specified vertices, if they exist.
	 * Parameters:
	 * -- (T&) v1      : source vertex id
	 * -- (T&) v2      : sink vertex id
	 * -- (double) w   : edge weight
	 * 
	 * Returns:
	 * -- true if and only if the edge was successfully added.
	 * -- false if the edge could not be added because of 1 of the following:
	 *    -> v1 and/or v2 don't exist in the graph
	 */
	bool addEdge(const T& v1, const T& v2, double w);

	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * Parameters:
	 * -- (T&) id : id of the vertex to remove from the graph.
	 * Returns:
	 * -- a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 * WRITE operation.
	 */
	GraphVertex<T>* removeVertex(const T& id);

	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * Parameters:
	 * -- (T&) id : id of the vertex to remove from the graph.
	 * Returns:
	 * -- a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 * WRITE operation.
	 */
	bool removeVertex(const GraphVertex<T>* v);

	/*
	 * Removes the specified edge from the graph.
	 * Parameters:
	 * -- (T&) v1 : source vertex id
	 * -- (T&) v2 : sink vertex id
	 * Returns:
	 * -- True iff an edge was removed.
	 */
	bool removeEdge(const T& v1, const T& v2);

	/*
	 * Removes the specified edge from the graph. 
	 * Parameters:
	 * -- (GraphVertex&) v1 : source vertex
	 * -- (GraphVertex&) v2 : sink vertex
	 * Returns:
	 * -- True iff an edge was removed.
	 */
	bool removeEdge(const GraphVertex<T>* v1, const GraphVertex<T>* v2);

	/*
	 * Removes all neighbors of the specified vertex from the graph. 
	 * WRITE operation.
	 */
	void removeAllNeighbors(const T& v);

	/*
	 * Removes all vertices and edges from the graph.
	 * WRITE operation. 
	 */
	void clear();

};


}

#endif
