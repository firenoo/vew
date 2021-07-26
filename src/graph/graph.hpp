#ifndef _FN_GRAPH
    #define _FN_GRAPH 
	#include <cstddef>
	#include <unordered_map>
	#include <functional>
	#include <optional>
	#include <memory>
	#include <type_traits>
	#include <vector>
/*
 * Author: firenoo
 * File created on 2021/04/21
 */
namespace firenoo {

	

	/*
	 * ---------------------------------------------------------------------------- 
	 * Graph
	 * ----------------------------------------------------------------------------
	 * A representation of a simple graph, which is a collections of vertices, V,
	 * and a collection edges E. Loops and multiedges are not supported.
	 * 
	 * Template Args:
	 * T - type of each vertex
	 * W - type of weight.
	 */
	template <
		class T,
		class W = double,
		class Hash = std::hash<T>,
		class KeyEq = std::equal_to<T>, 
		typename std::enable_if<std::is_arithmetic<W>::value, bool>::type = true
	> class Graph {
	public:
		class Vertex;
		class Edge;
	protected:
		std::unordered_map<T, std::unique_ptr<Vertex>, Hash, KeyEq> m_vertices;
		std::unordered_map<Vertex*, std::vector<Edge>> m_edges;
		std::size_t m_edgeCount = 0;
		//Gets the pointer to the vertex mapped by `v`.
		std::optional<Vertex*> getVertex(const T& v) const {
			auto it = m_vertices.find(v);
			if(it != m_vertices.end()) {
				return it->second.get();
			}
			return {};
		}
	public:
		class Vertex {
		protected:
			T m_obj;
			Graph* const m_g;
		public:
			
			Vertex(const T& obj, Graph* g) :
				m_obj(obj),
				m_g(g) {}
			
			inline T& get() {
				return m_obj;
			}

			inline T& operator*() {
				return m_obj;
			}

			inline T* operator->() {
				return &m_obj;
			}

			auto begin() const {
				return m_g->m_edges.find(m_g->m_vertices.at(m_obj).get())->second.begin();
			}

			auto end() const {
				return m_g->m_edges.find(m_g->m_vertices.at(m_obj).get())->second.end();
			}
		};
		
		class Edge {
			Vertex* m_target;
			W m_weight;

		public:
			Edge(Vertex* target, const W& weight) :
				m_target(target),
				m_weight(weight) {}

			Vertex* target() {
				return m_target;
			}

			const W& weight() const {
				return m_weight;
			}
		};

		Graph() {}

		virtual ~Graph() {
			clear();
		}

	//READ operations

		/*
		* Gets the number of vertices in this graph.
		* 
		* READ operation.
		* Returns:
		*  - an unsigned integer representing the total number of vertices
		*    stored in the graph.
		*/
		inline std::size_t vertexCount() const noexcept {
			return m_vertices.size();
		};
		
		/*
		* Gets the number of edges in this graph.
		*
		* READ operation.
		* Returns:
		*  - an integer representing the total number of edges in
		*    the graph.
		*/
		inline std::size_t edgeCount() const noexcept {
			return m_edgeCount;
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
		virtual inline bool hasVertex(const T& v) const {
			return m_vertices.find(v) != m_vertices.end();
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
		bool hasVertex(const T&& v) const {
			return hasVertex(v);
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
			auto vert1 = getVertex(v1);
			auto vert2 = getVertex(v2);
			if(vert1 && vert2) {
				auto v1_edges = m_edges.at(*vert1);
				for(auto edge : v1_edges) {
					if(edge.target() == vert2) {
						return true;
					}
				}
			}
			return false;
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
		bool hasEdge(const T& v1, const T&& v2) const {
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
		bool hasEdge(const T&& v1, const T& v2) const {
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
		bool hasEdge(const T&& v1, const T&& v2) const {
			return hasEdge(v1, v2);
		}

		/*
		* Gets the edge weight of edge (v1, v2).
		* 
		* READ operation.
		* Parameters:
		*  - v1 : source vertex to check.
		*  - v2 : sink vertex to check.
		* Returns:
		*  - A std::optional object, which contains the edge weight if
		*    the edge exists.
		*/
		virtual std::optional<W> getEdge(const T& v1, const T& v2) const {
			auto vert1 = getVertex(v1);
			auto vert2 = getVertex(v2);
			if(vert1 && vert2) {
				auto v1_edges = m_edges.at(*vert1);
				//O(n)
				for(auto edge : v1_edges) {
					if(edge.target() == *vert2) {
						return edge.weight();
					}
				}
			}
			return {};
		}

		std::optional<W> getEdge(const T& v1, const T&& v2) const {
			return getEdge(v1, v2);
		}

		std::optional<W> getEdge(const T&& v1, const T& v2) const {
			return getEdge(v1, v2);
		}

		std::optional<W> getEdge(const T&& v1, const T&& v2) const {
			return getEdge(v1, v2);
		}

		/*
		 * Gets a `std::vector` of all vertices in the graph.
		 * 
		 * READ operation.
		 * Returns:
		 *  - a vector that has all vertices of the graph
		 */
		virtual std::vector<Vertex*> vertices() const {
			std::vector<Vertex*> result;
			result.reserve(m_vertices.size());
			for(auto& [obj, vertex] : m_vertices) {
				result.push_back(vertex.get());
			}
			return result;
		}

		/*
		 * Gets a `std::vector` of all edges in the graph.
		 * 
		 * READ operation.
		 * Returns:
		 *  - a vector that has all edges of the graph
		 */
		virtual std::vector<std::pair<Vertex*, Edge>> edges() const {
			std::vector<std::pair<Vertex*, Edge>> result;
			result.reserve(m_edges.size());
			for(auto& [vertex, edgeList] : m_edges) {
				for(auto& edge : edgeList) {
					result.emplace_back(vertex, edge);
				}
			}
			return result;
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
		virtual bool addVertex(const T& v) {
			if(!hasVertex(v)) {
				m_vertices[v] = std::make_unique<Vertex>(v, this);
				m_edges[m_vertices[v].get()] = {};
				return true;
			}
			return false;
		}

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
		bool addVertex(const T&& v) {
			return addVertex(v);
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
		virtual bool removeVertex(const T& v) {
			if(hasVertex(v)) {
				Vertex* vptr = m_vertices[v].get();
				m_edges.erase(vptr);
				//delete edges to this vertex
				for(auto &[entry, edgelist] : m_edges) {
					removeEdge(**entry, v);
				}
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
		bool removeVertex(const T&& v) {
			return removeVertex(v);
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
		virtual bool addEdge(const T& v1, const T& v2, const W& w) {
			auto vertex1 = getVertex(v1);
			auto vertex2 = getVertex(v2);
			if(vertex1 && vertex2 && !hasEdge(v1, v2)) {
				m_edges[*vertex1].emplace_back(*vertex2, w);
				++m_edgeCount;
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
		bool addEdge(const T& v1, const T&& v2, W w) {
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
		bool addEdge(const T&& v1, const T& v2, W w) {
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
		bool addEdge(const T&& v1, const T&& v2, W w) {
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
		virtual bool removeEdge(const T& v1, const T& v2) = 0;

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
		bool removeEdge(const T& v1, const T&& v2) {
			return removeEdge(v1, v2);
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
		bool removeEdge(const T&& v1, const T& v2) {
			return removeEdge(v1, v2);
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
		bool removeEdge(const T&& v1, const T&& v2) {
			return removeEdge(v1, v2);
		}

		/*
		 * Removes all vertices and edges from the graph.
		 * WRITE operation. 
		 */
		void clear() {
			m_vertices.clear();
			m_edges.clear();
			m_edgeCount = 0;
		}
	};
}

#endif
