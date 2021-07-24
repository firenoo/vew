#ifndef _FN_UNDIRECTED_GRAPH
    #define _FN_UNDIRECTED_GRAPH 
	#include <cstddef>
	#include <memory>
	#include <unordered_set>
	#include "graph.hpp"

namespace firenoo {

/*
 * ----------------------------------------------------------------------------
 * UndirectedGraph
 * ----------------------------------------------------------------------------
 * Represents a weighted, undirected graph. Weights are represented by doubles
 * by default. The only difference between this class and GraphW is when
 * modifying an edge (u, v), the edge (v, u) is also modified. That is, the
 * following properties are guaranteed:
 * - (u, v) in E  <=> (v, u) in E
 * - w((u, v)) = w((v, u))
 * 
 * Template args:
 * T - type
 * W - weight type.
 * Hash - class that contains a hash function, see std::hash
 * KeyEq - class that contains eq function, see std::equal_to
 */
template<
	class T, 
	class W = double, 
	class Hash = std::hash<T>, 
	class KeyEq = std::equal_to<T>,	
	typename std::enable_if<std::is_arithmetic<W>::value, bool>::type = true
> class UndirectedGraph : public Graph<T, W, Hash, KeyEq> {
private:
	#define Graph Graph<T, W, Hash, KeyEq>
	using Vertex = typename Graph::Vertex;
	using Edge = typename Graph::Edge;
	//tracks edges and their index in the edge list.
	std::unordered_map<Vertex*, std::unordered_map<Vertex*, std::size_t>> m_edgeTracker;

public:
	/*
	 * Default constructor. Creates an empty graph with no vertices or edges.
	 */
	UndirectedGraph() : Graph() {}
	
	/*
	 * Default destructor, must delete all vertices and edges.
	 */
	~UndirectedGraph() {
		this->clear();
		m_edgeTracker.clear();
	}

// WRITE operations -----------------------------------------------------------

	bool hasEdge(const T& v1, const T& v2) const override {
		auto vertex1 = this->getVertex(v1);
		auto vertex2 = this->getVertex(v2);
		if(vertex1 && vertex2) {
			auto it = m_edgeTracker.at(*vertex2);
			return it.find(*vertex1) != it.end();
		}
		return false;
	}

	std::optional<W> getEdge(const T& v1, const T& v2) const override {
		auto vertex1 = this->getVertex(v1);
		auto vertex2 = this->getVertex(v2);	
		if(hasEdge(v1, v2)) {
			std::size_t index = m_edgeTracker.at(*vertex1).at(*vertex2);
			return this->m_edges.at(*vertex1).at(index).weight();
		}
		return false;
	}

	bool addVertex(const T& v) override {
		if(!this->hasVertex(v)) {
			this->m_vertices[v] = std::make_unique<Vertex>(v, this);
			Vertex* vptr = this->m_vertices[v].get();
			this->m_edges[vptr] = {};
			m_edgeTracker[vptr] = {};
			return true;
		}
		return false;
	}

	bool addEdge(const T& v1, const T& v2, const W& w) override {
		auto vertex1 = this->getVertex(v1);
		auto vertex2 = this->getVertex(v2);
		if(vertex1 && vertex2 && !hasEdge(v1, v2)) {
			auto v1_edgeList = this->m_edges[*vertex1];
			m_edgeTracker[*vertex1][*vertex2] = v1_edgeList.size();
			v1_edgeList.emplace_back(*vertex2, w);
			auto v2_edgeList = this->m_edges[*vertex2];
			m_edgeTracker[*vertex2][*vertex1] = v2_edgeList.size();
			v2_edgeList.emplace_back(*vertex1, w);
			++this->m_edgeCount;
			return true;
		}
		return false;
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
	bool removeVertex(const T& v) override {
		auto vertex = this->getVertex(v);
		if(vertex) {
			//delete all vertices
			for(auto& edge : **vertex) { 
				this->removeEdge(v, **(edge.vertex_2()));
			}
			return true;
		}
		return false;
	}

	bool removeEdge(const T& v1, const T& v2) override {
		auto vertex1 = this->getVertex(v1);
		auto vertex2 = this->getVertex(v2);
		if(vertex1 && vertex2 && hasEdge(v1, v2)) {
			std::size_t index1 = m_edgeTracker[*vertex1][*vertex2];
			std::size_t index2 = m_edgeTracker[*vertex2][*vertex1];
			m_edgeTracker[*vertex1].erase(*vertex2);
			m_edgeTracker[*vertex2].erase(*vertex1);
			this->m_edges[*vertex1].erase((*vertex1)->begin() + index1);
			this->m_edges[*vertex2].erase((*vertex2)->begin() + index2);
			for(auto it = (*vertex1)->begin() + index1; it != (*vertex1)->end(); ++it) {
				m_edgeTracker[*vertex1][it->vertex_2()] -= 1;
			}
			for(auto it = (*vertex2)->begin() + index2; it != (*vertex2)->end(); ++it) {
				m_edgeTracker[*vertex2][it->vertex_2()] -= 1;
			}
			--this->m_edgeCount;
			return true;
		}
		return false;
	}
};

#undef Graph
}

#endif