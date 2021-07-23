#ifndef _FN_GRAPHW
    #define _FN_GRAPHW
	#include <stack>
	#include <unordered_set>
	#include "graph.hpp"
/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {


	/*
	 * ----------------------------------------------------------------------------
	 * DirectedGraph
	 * ----------------------------------------------------------------------------
	 * Represents a weighted, directed graph. Weights are represented by doubles by
	 * default. Multiedges are not allowed.
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
	> class DirectedGraph : public Graph<T, W, Hash, KeyEq> {
	private:
		#define Graph Graph<T, W, Hash, KeyEq> 
		using Vertex = typename Graph::Vertex;
		using Edge = typename Graph::Edge;
		std::unordered_map<Vertex*, std::unordered_set<Vertex*>> m_backedges;

	public:
		/*
		* Default constructor. Creates an empty graph with no vertices or edges.
		*/
		DirectedGraph() : Graph() {}
		
	// READ operation

		/*
		* Creates a clone of this graph, reverses the clone's edges, and returns
		* the clone.
		* 
		* Returns:
		*  - A directed graph that contains all vertices of this graph but
		*    its edges are all reversed.
		*/
		DirectedGraph reverse() const {
			DirectedGraph result;
			if(Graph::vertexCount() <= 0) return result;
			//Run DFS, adding edges as we go.
			std::stack<Vertex*> work_stack;
			std::unordered_set<Vertex*> visited;
			for(auto &[key, vertex] : this->m_vertices) {
				work_stack.push(&vertex);
				result.addVertex(&vertex);
				while(!work_stack.empty()) {
					Vertex* vertex = work_stack.top();
					work_stack.pop();
					for(auto &[type, neighbor] : *vertex) {
						if(visited.find(&neighbor) == visited.end()) {
							visited.insert(vertex);
							work_stack.push(&neighbor);
							result.addVertex(type);
						}
						//Add edges and backedges
						W w = this->getEdge(key, type);
						result.addEdge(type, key);
					}
				}
			}
			return result;		
		}

		bool hasEdge(const T& v1, const T& v2) const override {
			auto vertex1 = this->getVertex(v1);
			auto vertex2 = this->getVertex(v2);
			if(vertex1 && vertex2) {
				auto it = m_backedges.at(*vertex2);
				return it.find(*vertex1) != it.end();
			}
			return false;
		}

	// WRITE operations -----------------------------------------------------------

		bool addVertex(const T& v) override {
			if(auto vertex = this->m_vertices.find(v); vertex == this->m_vertices.end()) {
				this->m_vertices[v] = std::make_unique<Vertex>(v);
				Vertex* vptr = this->m_vertices[v].get();
				this->m_edges[vptr] = std::vector<Edge>();
				m_backedges[vptr] = std::unordered_set<Vertex*>();
				return true;
			}
			return false;
		}

		bool addEdge(const T& v1, const T& v2, const W& w) override {
			auto vertex_1 = this->getVertex(v1);
			auto vertex_2 = this->getVertex(v2);
			if(vertex_1 && vertex_2 && !hasEdge(v1, v2)) {
				this->m_edges[*vertex_1].emplace_back(Edge(*vertex_2, w));
				m_backedges[*vertex_2].insert(*vertex_1);
				++this->m_edgeCount;
				return true;
			}
			return false;
		}

		bool removeVertex(const T& v) override {
			auto vertex = this->getVertex(v);
			if(vertex) {
				//Delete edges from this vertex
				for(auto& edge : this->m_edges[*vertex]) {
					m_backedges[edge.vertex_2()].erase(*vertex);
					--this->m_edgeCount;
				}
				this->m_edges.erase(*vertex);
				//Delete edges to this vertex
				for(auto& b_vertex : m_backedges[*vertex]) {
					removeEdge(**b_vertex, v);
				}
				m_backedges.erase(*vertex);
				this->m_vertices.erase(v);
				return true;
			}
			return false;
		}

		bool removeEdge(const T& v1, const T& v2) override {
			auto vertex1 = this->getVertex(v1);
			auto vertex2 = this->getVertex(v2);
			if(hasEdge(v1, v2)) {
				std::vector<Edge> v1_edges = this->m_edges[*vertex1];
				for(auto it = v1_edges.begin(); it != v1_edges.end(); ++it) {
					if(it->vertex_2() == *vertex2) {
						v1_edges.erase(it);
						break;
					}
				}
				--this->m_edgeCount;
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
		bool addBiEdge(const T& v1, const T& v2, W w) {
			bool s1 = this->addEdge(v1, v2, w);
			bool s2 = this->addEdge(v2, v1, w);
			return s1 && s2;
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
		bool addBiEdge(const T&& v1, const T&& v2, W w) {
			return addBiEdge(v1, v2, w);
		}

	};

	#undef Graph

}

#endif
