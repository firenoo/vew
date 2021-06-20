#ifndef _FN_GRAPH
    #define FN_GRAPH 0

/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

/*
 * ---------------------------------------------------------------------------- 
 * Graph (Superclass)
 * ----------------------------------------------------------------------------
 * A representation of a mathematical graph object. Submembers of this class are
 * named with the following suffixes to indicate properties of each 
 * implementation
 * 
 * Example: GraphU means that the graph implementation is unweighted, does not
 * multigraphs, and does not allow self-loops. In other words, it is a simple
 * unweighted graph.
 *  
 * The suffix order should respect the list below. 
 * 1. U / W - unweighted/weighted (must be one or the other)
 * 2. M - multigraph (multiple edges to the same vertex, optional)
 * 3. L - self-loops (edges from a vertex to itself, optional)
 * 
 * Note that all graphs have the following property(s):
 * Directed - an undirected graph is represented as a directed graph with 
 *            all edges going both ways.
 * 
 * 
 * Template Args:
 * T - type of each vertex
 * D - type of edge weight (if unweighted, bool suffices; if multigraph,
 * some list structure suffices)
 * V - type of vertex
 */
template<class T, class D, class V>
class Graph {

public:
	//READ operations
	virtual unsigned int vertexCount() const = 0;
	
	virtual unsigned int edgeCount() const = 0;

	virtual bool hasVertex(const T& v) const = 0;

	virtual bool hasEdge(const T& v1, const T& v2) const = 0;

	//WRITE operations

	virtual V* addVertex(const T& v) = 0;

	virtual bool addVertex(const V* v) = 0;

	virtual V* removeVertex(const T& v) = 0;

	virtual bool removeVertex(const V* v) = 0;

	virtual bool addEdge(const T& v1, const T& v2, D w) = 0;

	virtual bool removeEdge(const T& v1, const T& v2) = 0;

	virtual void clear() = 0;
};



}

#endif
