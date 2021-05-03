#ifndef _FN_GRAPH_VERTEX
    #define _FN_GRAPH_VERTEX 0
	#include <unordered_map>
	#include <string>

namespace firenoo {
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
	size_t _indegree;
	std::string _name;
	std::unordered_map<GraphVertex*, std::pair<std::string, double>> _edges;
public:
	GraphVertex(const std::string obj);

	~GraphVertex();
	
	/*
	 * Gets the value associated to this vertex.
	 * Parameters:
	 * -- None
	 * Returns:
	 * -- a const reference to the value.
	 * READ operation.
	 */
	const std::string& get() const;

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
	 * Determines whether an edge exists from this vertex to the specified
	 * vertex.
	 * Parameters:
	 * -- (GraphVertex*) other : the vertex to check
	 * Returns:
	 * -- true if and only if $other$ is a direct neighbor of this vertex.
	 *    Note that if an edge exists from $other$ to this vertex, this
	 *    method still returns false.
	 * READ operation.
	 */
	bool isNeighboring(const GraphVertex* other) const;

	/*
	 * Adds an edge to the current graph.
	 * Parameters:
	 * -- (GraphVertex*) other : the vertex the edge will point to
	 * -- (std::string) id     : the edge identifier. Fails if the id
	 * 						     already exists in the edge list.
	 * -- (double) weight      : edge weight
	 * Returns:
	 * -- true if and only if an edge was successfully added.
	 * WRITE operation.
	 */
	bool addEdge(const GraphVertex* other, const std::string id, double weight);
	
	/*
	 * Removes the specified edge.
	 * Parameters:
	 * -- (GraphVertex*) other : the other vertex that the edge points to
	 * -- (std::string&) id    : the edge identifier
	 * Returns:
	 * -- true if and only if an edge was successfully removed.
	 * WRITE operation.
	 */
	bool removeEdge(const GraphVertex* other, const std::string& id);

};

}
#endif
