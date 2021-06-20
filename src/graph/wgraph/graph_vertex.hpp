#ifndef _FN_GRAPH_VERTEX
    #define _FN_GRAPH_VERTEX 0
	#include <unordered_map>
	#include <set>
	#include <string>
	#include <vector>
namespace firenoo {
/*
 * ----------------------------------------------------------------------------
 * GraphVertex - no multiedges
 * ----------------------------------------------------------------------------
 * Representation of a general graph vertex.
 * _indegree: Cached value of the indegree, updated lazily.
 * _obj: An identifier for the vertex.
 * _neighbors: Neighbors of this graph vertex.
 */
template<class T>
class GraphVertex {	
protected:
	size_t _indegree;
	T* _obj;
	std::unordered_map<GraphVertex<T>*, double> _neighbors;

	/*
	 * Gets the edge weight associated with the specified vertex.
	 * Parameters:
	 * -- (GraphVertex*) other : Vertex to check. 
	 * Returns:
	 * -- The weight of the edge. Negative weights edges are allowed;
	 *    use hasEdge() to ensure that the result is valid.
	 * READ operation.
	 */
	double getEdge(GraphVertex<T>* const& other) const;
	
public:
	GraphVertex(const T& obj);

	~GraphVertex();
	
	/*
	 * Gets the value associated to this vertex.
	 * Parameters:
	 * -- None
	 * Returns:
	 * -- a const reference to the value.
	 * READ operation.
	 */
	const T& get() const;

	/*
	 * Gets the outdegree of this vertex.
	 * Returns:
	 * -- an unsigned int equal to the outdegree of this vertex.
	 * READ operation.
	 */
	size_t outdegree() const;

	/*
	 * Gets the indegree of this vertex.
	 * Returns:
	 * -- an unsigned int equal to the indegree of this vertex.
	 * READ operation.
	 */
	size_t indegree() const;

	/*
	 * Checks whether this vertex has an edge to the other vertex.
	 * Parameters:
	 * -- (GraphVertex*) other : Vertex to check.
	 * Returns:
	 * -- True iff there is an edge from this vertex to the other
	 *    vertex.
	 * READ operation.
	 */
	bool hasEdge(const GraphVertex<T>* other) const;

	/*
	 * Adds an edge to the current graph.
	 * Parameters:
	 * -- (GraphVertex*) other : the vertex the edge will point to
	 * -- (double) weight      : edge weight
	 * Returns:
	 * -- true if and only if an edge was successfully added.
	 * WRITE operation.
	 */
	bool addEdge(GraphVertex<T>* other, double weight);
	
	/*
	 * Removes the specified edge.
	 * Parameters:
	 * -- (GraphVertex*) other : the other vertex that the edge points to
	 * Returns:
	 * -- true if and only if an edge was successfully removed.
	 * WRITE operation.
	 */
	bool removeEdge(GraphVertex<T>* other);
};

}
#endif

