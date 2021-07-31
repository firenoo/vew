#ifndef _FN_DIRECTED_GRAPH
    #define _FN_DIRECTED_GRAPH
	#include <memory>
	#include <unordered_set>
	#include <stack>
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

		//Copy		
		DirectedGraph(DirectedGraph& other) : Graph(other) {
			for(auto &[vertex, set] : other.m_backedges) {
				auto v1 = this->m_vertices[**vertex].get();
				m_backedges[v1] = {};
				for(auto& it : set) {
					auto v2 = this->m_vertices[**it].get();
					m_backedges[v1].insert(v2);
				}
			}
		}

		//Move
		DirectedGraph(DirectedGraph&& other) : Graph(std::move(other)) {
			for(auto &[vertex, b_edges] : other.m_backedges) {
				m_backedges[vertex] = {};
				for(auto it = b_edges.begin(); it != b_edges.end();/**/) {
					m_backedges[vertex].insert(std::move(b_edges.extract(it++)));
				}
			}
		}

		~DirectedGraph() {
			this->clear();
			m_backedges.clear();
		}
	// READ operation

		/*
		* Creates a clone of this graph, reverses the clone's edges, and returns
		* the clone.
		* 
		* Note about the implementation: I tried to use return by value, only to
		* get compiler errors by copying `std::unique_ptr`. That's probably 
		* because I'm using -O0 for debugging. 
		* Parameter:
		*  - a directed graph to copy into. The graph must be empty, lest there
		*    be undefined behavior.
		* Returns:
		*  - A directed graph that contains all vertices of this graph but
		*    its edges are all reversed.
		*/
		void reverse(DirectedGraph& result) const {
			if(this->vertexCount() <= 0) return;
			//Run DFS, adding edges as we go.
			std::stack<Vertex*> work_stack = {};
			std::unordered_set<Vertex*> visited = {};
			visited.reserve(this->vertexCount());
			for(auto &[key, vptr] : this->m_vertices) {
				if(visited.find(vptr.get()) != visited.end()) continue;
				work_stack.push(vptr.get());
				result.addVertex(key);
				visited.insert(vptr.get());
				while(!work_stack.empty()) {
					Vertex* nextVertex = work_stack.top();
					work_stack.pop();
					for(auto& edge : *nextVertex) {
						auto& t = **(edge.target());
						if(visited.find(edge.target()) == visited.end()) {
							visited.insert(edge.target());
							work_stack.push(edge.target());
							result.addVertex(t);
						}
						//Add edges and backedges
						auto w = this->getEdge(**nextVertex, t);
						result.addEdge(t, **nextVertex, *w);
					}
				}
			}
		}

		bool hasEdge(const T& v1, const T& v2) const override {
			auto vertex1 = this->getVertex(v1);
			auto vertex2 = this->getVertex(v2);
			if(vertex1 && vertex2) {
				auto& it = m_backedges.at(*vertex2);
				return it.find(*vertex1) != it.end();
			}
			return false;
		}

	// WRITE operations -----------------------------------------------------------

		bool addVertex(const T& v) override {
			if(auto vertex = this->m_vertices.find(v); vertex == this->m_vertices.end()) {
				this->m_vertices[v] = std::make_unique<Vertex>(v, this);
				Vertex* vptr = this->m_vertices[v].get();
				this->m_edges[vptr] = {};
				m_backedges[vptr] = {};
				return true;
			}
			return false;
		}

		bool addEdge(const T& v1, const T& v2, const W& w) override {
			auto vertex1 = this->getVertex(v1);
			auto vertex2 = this->getVertex(v2);
			if(vertex1 && vertex2 && !hasEdge(v1, v2)) {
				this->m_edges[*vertex1].emplace_back(*vertex2, w);
				m_backedges[*vertex2].insert(*vertex1);
				++this->m_edgeCount;
				return true;
			}
			return false;
		}

		bool removeVertex(const T& v) override {
			auto vertex = this->getVertex(v);
			if(vertex) {
				//Delete edges from this vertex
				for(auto& neighbor : **vertex) {
					m_backedges[neighbor.target()].erase(*vertex);
					--this->m_edgeCount;
				}
				//Delete edges to this vertex
				//Iterate through backedges. typeof(b_edge) = Vertex*
				for(auto& b_edge : m_backedges[*vertex]) {
					//Find the edge in the edge list. typeof(it) = Edge
					for(auto it = b_edge->begin(); it != b_edge->end(); ++it) {
						if(it->target() == *vertex) {
							this->m_edges[b_edge].erase(it); //delete when found
							--this->m_edgeCount;
							break;
						}
					}
				}
				//clean up
				m_backedges.erase(*vertex);
				this->m_edges.erase(*vertex);
				this->m_vertices.erase(v);
				return true;
			}
			return false;
		}

		bool removeEdge(const T& v1, const T& v2) override {
			if(hasEdge(v1, v2)) {
				auto vertex1 = this->getVertex(v1);
				auto vertex2 = this->getVertex(v2);
				auto& v1_edges = this->m_edges[*vertex1];
				for(auto it = v1_edges.begin(); it != v1_edges.end(); ++it) {
					if(it->target() == *vertex2) {
						m_backedges[*vertex2].erase(*vertex1);
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
		* WRITE operation.
		* Parameters:
		*  - v1 : source vertex
		*  - v2 : sink vertex
		*  -  w : edge weight
		* 
		* Returns:
		*  - true if and only if the edges were added.
		*/
		bool addBiEdge(const T& v1, const T&& v2, W w) {
			return addBiEdge(v1, v2, w);
		}

		/*
		* Adds two edges (v1, v2) and (v2, v1) to the graph.
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
		bool addBiEdge(const T&& v1, const T& v2, W w) {
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

		DirectedGraph& operator=(DirectedGraph& other) {
			Graph::operator=(other);
			for(auto &[vertex, set] : other.m_backedges) {
				auto v1 = this->m_vertices[**vertex].get();
				m_backedges[v1] = {};
				for(auto& it : set) {
					auto v2 = this->m_vertices[**it].get();
					m_backedges[v1].insert(v2);
				}
			}
		}

		DirectedGraph& operator=(DirectedGraph&& other) {
			Graph::operator=(std::move(other));
			for(auto &[vertex, set] : other.m_backedges) {
				auto v1 = this->m_vertices[**vertex].get();
				m_backedges[v1] = {};
				for(auto& it : set) {
					auto v2 = this->m_vertices[**it].get();
					m_backedges[v1].insert(v2);
				}
			}
			return *this;
		}

		#undef Graph
	};
}

#endif
