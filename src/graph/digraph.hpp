#ifndef _FN_GRAPHW
    #define _FN_GRAPHW 0
	#include <stack>
	#include "vertexw.hpp"
	#include "graph.hpp"
/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

#define Vertex GraphVertexW<T, W>
#define Graph Graph<T, W, Vertex, Hash, KeyEq>
/*
 * ----------------------------------------------------------------------------
 * DirectedGraph
 * ----------------------------------------------------------------------------
 * Represents a weighted, directed graph. Weights are represented by doubles by
 * default.
 * 
 * Template args:
 * T - type
 * W - weight type.
 * Hash - class that contains a hash function, see std::hash
 * KeyEq - class that contains eq function, see std::equal_to
 */
template<class T, class W = double, class Hash = std::hash<T>, class KeyEq = std::equal_to<T>>
class DirectedGraph : public Graph {

public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	DirectedGraph() : Graph() {}
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~DirectedGraph() {
		Graph::clear();
	}
// READ operation

	/*
	 * Creates a clone of this graph, reverses the clone's edges, and returns
	 * the clone.
	 * 
	 * Returns:
	 *  - A directed graph that contains all vertices of this graph but
	 *    its edges are all reversed.
	 */
	virtual DirectedGraph r() const {
		DirectedGraph result;
		if(Graph::vertexCount() <= 0) return result;
		//Run DFS, adding edges as we go.
		std::stack<Vertex*> work_stack;
		std::unordered_set<Vertex*> visited;
		for(auto iter : Graph::_vertices) {
			work_stack.push(iter.second);
			result.addVertex(iter.second);
			while(!work_stack.empty()) {
				Vertex* vertex = work_stack.top();
				work_stack.pop();
				if(visited.find(vertex) != visited.end()) continue;
				visited.insert(vertex);
				auto i = vertex->neighbors();
				while(i != vertex->neighborsEnd()) {
					//Expand vertices
					if(visited.find(i->first) == visited.end()) {
						work_stack.push(i->first);
						result.addVertex(i->first);
					}
					W w;
					//Edge reversal
					vertex->getEdge(i->first, w);
					result.addEdge(i->first->get(), vertex->get(), w);
					++i;
				}
			}
		}
		return result;		
	}

// WRITE operations -----------------------------------------------------------

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * Memory: A new GraphVertexW* object is allocated on heap.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - a pointer to the new vertex if it was created, or a pointer to the 
	 *    existing vertex.
	 */
	virtual Vertex* addVertex(const T& v) override {
		auto vertex = Graph::_vertices.find(v);
		if(vertex == Graph::_vertices.end()) {
			Vertex* vertex_new = new Vertex(v);
			Graph::_vertices[v] = vertex_new;
			return vertex_new;
		}
		return vertex->second;
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T& v1, const T& v2, W w) {
		return Graph::addEdge(v1, v2, w) && Graph::addEdge(v2, v1, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T& v1, const T&& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T&& v1, const T& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const T&& v1, const T&& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * 
	 * Memory: No memory is freed. It is safe to free the pointer returned.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 */
	virtual Vertex* removeVertex(const T& v) override {
		Vertex* vert = Graph::removeVertex(v);
		vert->clearIndegree();
		return vert;
	}
};

#undef Vertex
#undef Graph
#define Vertex GraphVertexW<int, W>
#define Graph Graph<int, W, Vertex, Hash, KeyEq>
/*
 * ----------------------------------------------------------------------------
 * DirectedGraph (int)
 * ----------------------------------------------------------------------------
 * Represents a weighted, directed graph. Weights are represented by doubles by
 * default.
 * 
 * Template args:
 * W - weight type.
 * Hash - class that contains a hash function, see std::hash
 * KeyEq - class that contains eq function, see std::equal_to
 */
template<class W, class Hash, class KeyEq>
class DirectedGraph<int, W, Hash, KeyEq> : public Graph {

public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	DirectedGraph() : Graph() {}
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~DirectedGraph() {
		Graph::clear();
	}
//READ operation

	/*
	 * Creates a clone of this graph, reverses the clone's edges, and returns
	 * the result.
	 */
	virtual DirectedGraph r() {
		DirectedGraph result;
		if(Graph::vertexCount() <= 0) return result;
		//Run DFS, adding edges as we go.
		std::stack<Vertex*> work_stack;
		std::unordered_set<Vertex*> visited;
		for(auto iter : Graph::_vertices) {
			work_stack.push(iter.second);
			result.addVertex(iter.second);
			while(!work_stack.empty()) {
				Vertex* vertex = work_stack.top();
				work_stack.pop();
				if(visited.find(vertex) != visited.end()) continue;
				visited.insert(vertex);
				auto i = vertex->neighbors();
				while(i != vertex->neighborsEnd()) {
					if(visited.find(i->first) == visited.end()) {
						work_stack.push(i->first);
						result.addVertex(i->first);
					}
					W w;
					vertex->getEdge(i->first, w);
					result.addEdge(i->first->get(), vertex->get(), w);
					++i;
				}
			}
		}
		return result;		
	}

// WRITE operations -----------------------------------------------------------

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * Memory: A new GraphVertexW* object is allocated on heap.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - a pointer to the new vertex if it was created, or a pointer to the 
	 *    existing vertex.
	 */
	virtual Vertex* addVertex(const int& v) override {
		auto vertex = Graph::_vertices.find(v);
		if(vertex == Graph::_vertices.end()) {
			Vertex* vertex_new = new Vertex(v);
			Graph::_vertices[v] = vertex_new;
			return vertex_new;
		}
		return vertex->second;
	}

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 *
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - true if and only if a vertex was added.
	 */
	virtual bool addVertex(Vertex* v) override {
		if(!Graph::hasVertex(v->get())) {
			Graph::_vertices[v->get()] = v;
			return true;
		}
		return false;
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int& v1, const int& v2, W w) {
		return Graph::addEdge(v1, v2, w) && Graph::addEdge(v2, v1, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int& v1, const int&& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int&& v1, const int& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	/*
	 * Adds two edges (v1, v2) and (v2, v1) to the graph.
	 * 
	 * Memory: No memory is allocated nor freed.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v1 : source vertex
	 *  - v2 : sink vertex
	 *  -  w : edge weight
	 * 
	 * Returns:
	 *  - true if and only if the edges were added.
	 */
	virtual bool addBiEdge(const int&& v1, const int&& v2, W w) {
		return addBiEdge(v1, v2, w);
	}

	virtual Vertex* removeVertex(const int& v) override {
		Vertex* vert = Graph::removeVertex(v);
		vert->clearIndegree();
		return vert;
	}

	/*
	 * Removes the specified vertex from the graph. Does nothing if the vertex
	 * was not in the graph.
	 * 
	 * Memory: No memory is freed. It is safe to free the pointer returned.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - a pointer to the vertex that was removed, or nullptr if no vertex was
	 *    removed
	 */
	virtual bool removeVertex(Vertex* v) override {
		if(Graph::removeVertex(v)) {
			v->clearIndegree();
			return true;
		}
		return false;;
	}
};
#undef Vertex
#undef Graph
}

#endif
