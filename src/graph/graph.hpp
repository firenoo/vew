#ifndef GRAPH
    #define GRAPH 0
	#pragma once
	#include <unordered_map>
	#include <string>
#endif
/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

/*
 * ----------------------------------------------------------------------------
 *                                   Graph
 * ----------------------------------------------------------------------------
 * Representation of a directed, weighted graph. Multiedges are allowed.
 */
class Graph {
private:
	std::unordered_map<std::string, GraphVertex*> vertices;
	unsigned int _edgeCount;

	/*
	 * Adds the specified vertex to the graph. If the object already
	 * exists, this method does nothing and returns false.
	 * Parameters:
	 * -- (GraphVertex&) v : vertex object to add to the graph.
	 * Returns:
	 * -- true if and only if the vertex was added to the graph.
	 * WRITE operation.
	 */
	bool addVertex(const GraphVertex* v);

	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * Parameters:
	 * -- (GraphVertex&) v : vertex object to remove from the graph
	 * Returns:
	 * -- a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 * WRITE operation.
	 */
	GraphVertex* removeVertex(const GraphVertex* v);
public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	Graph();
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~Graph();
	
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
	bool hasVertex(const std::string& v) const;

// WRITE operations -----------------------------------------------------------

	/*
	 * Adds the specified object as a vertex to the graph. If the object already
	 * exists, this method does nothing and returns false.
	 * Parameters:
	 * -- (std::string&) id : name of the vertex.
	 * Returns:
	 * -- a pointer to the vertex if it was created, or nullptr if operation
	 *    failed.
	 * WRITE operation.
	 */
	GraphVertex* addVertex(const std::string& id);



	/*
	 * Adds a directed edge between the two specified vertices, if they exist.
	 * Parameters:
	 * -- (std::string&) v1      : source vertex id
	 * -- (std::string&) v2      : sink vertex id
	 * -- (std::string&) id      : edge id
	 * -- (double) w             : edge weight
	 * 
	 * Returns:
	 * -- true if and only if the edge was successfully added.
	 * -- false if the edge could not be added because of 1 of the following:
	 *    -> v1 and/or v2 don't exist in the graph
	 */
	bool addEdge(const std::string& v1, const std::string& v2, const std::string& id, double w);

	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * Parameters:
	 * -- (std::string&) id : id of the vertex to remove from the graph.
	 * Returns:
	 * -- a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 * WRITE operation.
	 */
	GraphVertex* removeVertex(const std::string& id);



	/*
	 * Removes the specified edge from the graph.
	 * Parameters:
	 * -- (GraphVertex&) v1 : source vertex id
	 * -- (GraphVertex&) v2 : sink vertex id
	 * -- (std::string) id  : edge id
	 */
	void removeEdge(const std::string& v1, const std::string& v2, const std::string& id);

	/*
	 * Removes the specified edge from the graph.
	 * Parameters:
	 * -- (GraphVertex&) v1 : source vertex
	 * -- (GraphVertex&) v2 : sink vertex
	 * --
	 */
	void removeEdge(const GraphVertex* v1, const GraphVertex* v2, const std::string& id);

};

/*
 * ----------------------------------------------------------------------------
 *                                GraphVertex
 * ----------------------------------------------------------------------------
 * Representation of a graph vertex.
 * Template parameters:
 * -- V : vertex type.
 */
class GraphVertex {	
protected:
	unsigned int indegree;
	std::string name;
	std::unordered_map<std::string, std::pair<GraphVertex*, double>> edges;

	ConstEdgeIterator begin();

public:
	GraphVertex(const std::string& obj);

	/*
	 * Gets the value associated to this vertex.
	 * Parameters:
	 * -- None
	 * Returns:
	 * -- a const reference to the value.
	 */
	std::string& get() const;

	/*
	 * Gets the outdegree of this vertex.
	 * Returns:
	 * -- an unsigned int equal to the outdegree of this vertex.
	 * READ operation.
	 */
	unsigned int outdegree() const;

	/*
	 * Gets the indegree of this vertex.
	 * Returns:
	 * -- an unsigned int equal to the indegree of this vertex.
	 * READ operation.
	 */
	unsigned int indegree() const;

	/*
	 * Determines whether an edge exists from this vertex to the specified
	 * vertex.
	 * Parameters:
	 * -- (GraphVertex*) other : the vertex to check
	 * Returns:
	 * -- true if and only if ## other ## is a direct neighbor of this vertex
	 */
	bool isNeighboring(const GraphVertex* other) const;

	/*
	 * Adds an edge to the current graph.
	 * Parameters:
	 * -- (GraphVertex*) other : the vertex the edge will point to
	 * -- (std::string&) id    : the edge identifier
	 * -- (double) weight      : edge weight
	 * Returns:
	 * -- true if and only if an edge was successfully added.
	 */
	bool addEdge(const GraphVertex* other, const std::string& id, double weight);
	
};

class ConstEdgeIterator {
private:
	GraphVertex v;

public:

	ConstEdgeIterator();

};

}
