#ifndef _FN_GRAPH
    #define _FN_GRAPH 0
	#include <unordered_map>
	#include <functional>

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
template<class T, class W, class V, class Hash = std::hash<T>, class KeyEq = std::equal_to<T>>
class Graph {
private:
	template<class X, class Y>
	friend class DirectedGraph;
	template<class X, class Y>
	friend class UndirectedGraph;

protected:
	std::unordered_map<std::reference_wrapper<const T>, V*, Hash, KeyEq> _vertices;
	size_t _edgeCount;

public:

	Graph() : _edgeCount(0) {}

	virtual ~Graph() {
		clear();
	};

//READ operations

	/*
	 * Gets the number of vertices in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - an unsigned integer representing the total number of vertices
	 *    stored in the graph.
	 */
	virtual size_t vertexCount() const noexcept {
		return _vertices.size();
	};
	
	/*
	 * Gets the number of edges in this graph.
	 *
	 * READ operation.
	 * Returns:
	 *  - an integer representing the total number of edges in
	 *    the graph.
	 */
	virtual size_t edgeCount() const {
		return _edgeCount;
	};

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const T& v) const {
		return _vertices.find(v) != _vertices.end();
	};

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const T&& v) const {
		return _vertices.find(v) != _vertices.end();
	};

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
	virtual bool hasEdge(const T& v1, const T& v2) const {
		auto vertex1 = _vertices.find(v1);
		auto vertex2 = _vertices.find(v2);
		return vertex1 != _vertices.end() && 
		       vertex2 != _vertices.end() && 
			   vertex1->second->hasEdge(vertex2->second);
	}
	
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
	virtual bool hasEdge(const T& v1, const T&& v2) const {
		return hasEdge(v1, v2);
	}	
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
	virtual bool hasEdge(const T&& v1, const T& v2) const {
		return hasEdge(v1, v2);
	}	
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
	virtual bool hasEdge(const T&& v1, const T&& v2) const {
		return hasEdge(v1, v2);
	}

	/*
	 * Gets the edge weight of edge (v1, v2), and stores it in `in`.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex to check.
	 *  - v2 : sink vertex to check.
	 * Returns:
	 *  - true if and only if the edge weight was read in successfully.
	 */
	virtual bool getEdge(const T& v1, const T& v2, W& in) const {
		if(hasEdge(v1, v2)) {
			_vertices.find(v1)->second->getEdge(_vertices.find(v2)->second, in);
			return true;
		}
		return false;
	}

	virtual bool getEdge(const T& v1, const T&& v2, W& in) const {
		return getEdge(v1, v2, in);
	}

	virtual bool getEdge(const T&& v1, const T& v2, W& in) const {
		return getEdge(v1, v2, in);
	}

	virtual bool getEdge(const T&& v1, const T&& v2, W& in) const {
		return getEdge(v1, v2, in);
	}

	/*
	 * Gets an iterator to an arbitrary vertex in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to some pairing (T, GraphVertexW<T, W>*)
	 *    in this graph.
	 */
	virtual typename std::unordered_map<T, V*>::const_iterator begin() const {
		return _vertices.cbegin();
	}

	/*
	 * Gets the end iterator for the vertex set in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to the end iterator.
	 */
	virtual typename std::unordered_map<T, V*>::const_iterator end() const {
		return _vertices.cend();
	}

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
	virtual V* addVertex(const T&& v) {
		return addVertex(v);
	};

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - true if and only if a vertex was added.
	 */
	virtual bool addVertex(V* v) {
		if(!hasVertex(v->get())) {
			_vertices[v->get()] = v;
			return true;
		}
		return false;
	}

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
	virtual V* removeVertex(const T& v) {
		auto search = _vertices.find(v->get());
		if(search != _vertices.end()) {
			V* vert = search->second;
			vert->clearIndegree();
			_vertices.erase(search);
			return true;
		}
		return false;
	};

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
	virtual V* removeVertex(const T&& v) {
		return removeVertex(v);
	};

	/*
	 * Removes the specified vertex from the graph. This operation
	 * does NOT free the pointer passed in.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - true if and only if the vertex was removed.
	 */
	virtual bool removeVertex(V* v) {
		auto search = _vertices.find(v->get());
		if(search != _vertices.end()) {
			V* vert = search->second;
			vert->clearEdges();
			_vertices.erase(search);
			return true;
		}
		return false;
	};

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
	virtual bool addEdge(const T& v1, const T& v2, W w) {
		if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
			V* src = _vertices[v1];
			V* snk = _vertices[v2];
			++_edgeCount;
			src->addEdge(snk, w);
			return true;
		}
		return false;
	};

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
	virtual bool addEdge(const T& v1, const T&& v2, W w) {
		return addEdge(v1, v2, w);
	}

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
	virtual bool addEdge(const T&& v1, const T& v2, W w) {
		return addEdge(v1, v2, w);
	}

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
	virtual bool addEdge(const T&& v1, const T&& v2, W w) {
		return addEdge(v1, v2, w);
	}

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
	virtual bool removeEdge(const T& v1, const T& v2) {
		auto src = _vertices.find(v1);
		auto snk = _vertices.find(v2);
		if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
			src->second->removeEdge(snk->second);
			--_edgeCount;
			return true;
		}
		return false;
	};

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
	virtual bool removeEdge(const T&& v1, const T&& v2) {
		return removeEdge(v1, v2);
	};

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex 
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const T& v) {
		auto query = _vertices.find(v);
		if(query != _vertices.end()) {
			V* vertex = query->second;
			_edgeCount -= vertex->outdegree();
			vertex->clearEdges();
			return true;
		}
		return false;
	};

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const T&& v) {
		return removeNeighbors(v);
	}

	/*
	 * Removes all vertices and edges from the graph.
	 * WRITE operation. 
	 */
	virtual void clear() {
		for(auto v : _vertices) {
			delete v.second;
		}
		_vertices.clear();
		_edgeCount = 0;
	}
};

/*
 * ---------------------------------------------------------------------------- 
 * Graph (int specialization)
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
template<class W, class V, class Hash, class KeyEq>
class Graph<int, W, V, Hash, KeyEq> {

protected:
	std::unordered_map<int, V*, Hash, KeyEq> _vertices;
	size_t _edgeCount;

public:

	Graph() : _edgeCount(0) {}

	virtual ~Graph() {
		clear();
	};

//READ operations

	/*
	 * Gets the number of vertices in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - an unsigned integer representing the total number of vertices
	 *    stored in the graph.
	 */
	virtual size_t vertexCount() const noexcept {
		return _vertices.size();
	};
	
	/*
	 * Gets the number of edges in this graph.
	 *
	 * READ operation.
	 * Returns:
	 *  - an integer representing the total number of edges in
	 *    the graph.
	 */
	virtual size_t edgeCount() const {
		return _edgeCount;
	};

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 *
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const int& v) const {
		return _vertices.find(v) != _vertices.end();
	};

	/*
	 * Checks whether the specified vertex object exists in the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v : vertex to check.
	 * Returns:
	 *  - true if and only if the vertex object exists in this graph
	 */
	virtual bool hasVertex(const int&& v) const {
		return _vertices.find(v) != _vertices.end();
	};

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
	virtual bool hasEdge(const int& v1, const int& v2) const {
		auto vertex1 = _vertices.find(v1);
		auto vertex2 = _vertices.find(v2);
		return vertex1 != _vertices.end() && 
		       vertex2 != _vertices.end() && 
			   vertex1->second->hasEdge(vertex2->second);
	}
	
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
	virtual bool hasEdge(const int& v1, const int&& v2) const {
		return hasEdge(v1, v2);
	}	
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
	virtual bool hasEdge(const int&& v1, const int& v2) const {
		return hasEdge(v1, v2);
	}	
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
	virtual bool hasEdge(const int&& v1, const int&& v2) const {
		return hasEdge(v1, v2);
	}	

	/*
	 * Gets the edge weight of edge (v1, v2), and stores it in `in`.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - v1 : source vertex to check.
	 *  - v2 : sink vertex to check.
	 * Returns:
	 *  - true if and only if the edge weight was read in successfully.
	 */
	virtual bool getEdge(const int& v1, const int& v2, W& in) const {
		if(hasEdge(v1, v2)) {
			_vertices.find(v1)->second->getEdge(_vertices.find(v2)->second, in);
			return true;
		}
		return false;
	}

	virtual bool getEdge(const int& v1, const int&& v2, W& in) const {
		return getEdge(v1, v2, in);
	}

	virtual bool getEdge(const int&& v1, const int& v2, W& in) const {
		return getEdge(v1, v2, in);
	}

	virtual bool getEdge(const int&& v1, const int&& v2, W& in) const {
		return getEdge(v1, v2, in);
	}

	/*
	 * Gets an iterator to an arbitrary vertex in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to some pairing (T, GraphVertexW<T, W>*)
	 *    in this graph.
	 */
	virtual typename std::unordered_map<int, V*>::const_iterator begin() const {
		return _vertices.cbegin();
	}

	/*
	 * Gets the end iterator for the vertex set in this graph.
	 * 
	 * READ operation.
	 * Returns:
	 *  - a const_iterator that points to the end iterator.
	 */
	virtual typename std::unordered_map<int, V*>::const_iterator end() const {
		return _vertices.cend();
	}

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
	virtual V* addVertex(const int& v) = 0;

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
	virtual V* addVertex(const int&& v) {
		return addVertex(v);
	}

	/*
	 * Adds the vertex to the graph if it doesn't exist already.
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : the object backing the vertex.
	 * Returns:
	 *  - true if and only if a vertex was added.
	 */
	virtual bool addVertex(V* v) {
		if(!hasVertex(v->get())) {
			_vertices[v->get()] = v;
			return true;
		}
		return false;
	};

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
	virtual V* removeVertex(const int& v) {
		auto search = _vertices.find(v);
		if(search == _vertices.end()) {
			return nullptr;
		}
		V* vert = search->second;
		_vertices.erase(search);
		return vert;
	}

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
	virtual V* removeVertex(const int&& v) {
		return removeVertex(v);
	}

	/*
	 * Removes the specified vertex from the graph. 
	 * 
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex to remove from the graph.
	 * Returns:
	 *  - true if and only if the vertex was removed.
	 */
	virtual bool removeVertex(V* v) {
		auto search = _vertices.find(v->get());
		if(search != _vertices.end()) {
			V* vert = search->second;
			vert->clearEdges();
			_vertices.erase(search);
			return true;
		}
		return false;
	}

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
	virtual bool addEdge(const int& v1, const int& v2, W w) {
		if(hasVertex(v1) && hasVertex(v2) && !hasEdge(v1, v2)) {
			V* src = _vertices[v1];
			V* snk = _vertices[v2];
			++_edgeCount;
			src->addEdge(snk, w);
			return true;
		}
		return false;
	};

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
	virtual bool addEdge(const int& v1, const int&& v2, W w) {
		return addEdge(v1, v2, w);
	}

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
	virtual bool addEdge(const int&& v1, const int& v2, W w) {
		return addEdge(v1, v2, w);
	}

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
	virtual bool addEdge(const int&& v1, const int&& v2, W w) {
		return addEdge(v1, v2, w);
	}

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
	virtual bool removeEdge(const int& v1, const int& v2) {
		auto src = _vertices.find(v1);
		auto snk = _vertices.find(v2);
		if(src != _vertices.end() && snk != _vertices.end() && hasEdge(v1, v2)) {
			src->second->removeEdge(snk->second);
			--_edgeCount;
			return true;
		}
		return false;
	};

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
	virtual bool removeEdge(const int&& v1, const int&& v2) {
		return removeEdge(v1, v2);
	};

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex 
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const int& v) {
		auto query = _vertices.find(v);
		if(query != _vertices.end()) {
			V* vertex = query->second;
			_edgeCount -= vertex->outdegree();
			vertex->clearEdges();
			return true;
		}
		return false;
	};

	/*
	 * The specified vertex has edges from it removed.
	 * WRITE operation.
	 * Parameters:
	 *  - v : vertex
	 * Returns:
	 *  - true if and only if all edges were removed.
	 */
	virtual bool removeNeighbors(const int&& v) {
		return removeNeighbors(v);
	}

	/*
	 * Removes all vertices and edges from the graph.
	 * WRITE operation. 
	 */
	virtual void clear() {
		for(auto v : _vertices) {
			delete v.second;
		}
		_vertices.clear();
		_edgeCount = 0;
	}
};

}

#endif
