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
 * Template parameters:
 * -- V         : type of the graph, used as an identifier. 
 *                Default uses std::string.
 * -- VertexObj : type used to represent a vertex. 
 *                Default uses firenoo::GraphVertex<V>.
 * -- Storage   : type used to store the vertices. 
 *                Default uses std::unordered_map<V, VertexObj>
 */
template<
	class V = std::string, 
	class Vertex = GraphVertex<V>, 
	class Storage = std::unordered_map<V, Vertex*>>
class Graph {
private:
	Storage vertices;
	unsigned int edgeCount;
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
	bool hasVertex(const V& v) const;

// WRITE operations -----------------------------------------------------------

	/*
	 * Adds the specified object as a vertex to the graph. If the object already
	 * exists, this method does nothing and returns false.
	 * Parameters:
	 * -- (V&) v : vertex value to be wrapped by a Vertex object.
	 * Returns:
	 * -- true if and only if the object was added to the graph.
	 * WRITE operation.
	 */
	bool addVertex(constV& v);

	/*
	 * Adds the specified vertex to the graph. If the object already
	 * exists, this method does nothing and returns false.
	 * Parameters:
	 * -- (Vertex&) v : vertex object to add to the graph.
	 * Returns:
	 * -- true if and only if the vertex was added to the graph.
	 * WRITE operation.
	 */
	bool addVertex(const Vertex& v);

	/*
	 * Adds a directed edge between the two specified vertices, if they exist.
	 * Use force=true to add the vertices if they don't before.
	 * Parameters:
	 * -- (V&) v1      : vertex 1, the source vertex value
	 * -- (V&) v2      : vertex 2, the destination vertex value
	 * -- (bool) force : If true, attempts to add v1 and v2 to the graph 
	 *                   before adding the edge.
	 * Returns:
	 * -- true if and only if the edge was successfully added.
	 * -- false if the edge could not be added because of 1 of the following:
	 *    -> v1 and/or v2 don't exist in the graph and force=false
	 *    -> v1 and/or v2 don't exist, force=true, but could not add v1 and/or
	 *       v2 to the graph.
	 */
	bool addEdge(const V& v1, const V& v2, bool force);

	/*
	 * Removes the specified vertex value from the graph.
	 * Parameters:
	 * -- (V&) v - vertex value to remove from the graph.
	 * Returns:
	 * -- the vertex object that was removed.
	 * WRITE operation.
	 */
	V& removeVertex(const V& v);

	/*
	 * Removes the specified vertex from the graph.
	 * Parameters:
	 * -- (Vertex&) v - vertex object to remove from the graph.
	 * Returns:
	 * -- the vertex object that was removed.
	 * WRITE operation.
	 */
	V& removeVertex(const Vertex& v);

};

/*
 * ----------------------------------------------------------------------------
 *                                GraphVertex
 * ----------------------------------------------------------------------------
 * Representation of a graph vertex.
 * Template parameters:
 * -- V : vertex type.
 */
template<class V>
class GraphVertex {
private:
	V obj;
	std::unordered_map<V, std::pair<GraphVertex*, double>> edges;
	
protected:
	unsigned int indegree;

public:
	GraphVertex(V& obj);

	/*
	 * Gets the value associated to this vertex.
	 * Parameters:
	 * -- None
	 * Returns:
	 * -- a const reference to the value.
	 */
	const V& get() const;

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


};

}