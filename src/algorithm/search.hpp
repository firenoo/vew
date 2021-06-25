#ifndef _FN_SEARCH
	#define _FN_SEARCH 0
	#include <vector>
	#include <stack>
	#include "graphw.hpp"
	#include "graphwb.hpp"
namespace firenoo {

	/*
	 * The result of DFS searching. Includes pre- and post- numbers. 
	 */
	template<typename Vertex>
	struct DFSResult {

		/*
		 * Pre-numbering
		 */
		size_t _pre;

		/*
		 * Post-numbering
		 */
		size_t _post;

		Vertex* _vertex;
	};

	template<class T>
	using DFSComponent = std::vector<T>;

	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Starts on an arbitrary vertex.
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphW instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being another std::vector (DFSComponent)
	 *    of vertices that are connected (in no particular order)
	 */ 
	template<class T, class W>
	std::vector<DFSComponent<GraphVertexW<T, W>*>> dfs_cc(const GraphW<T, W>& g);

	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Starts on an arbitrary vertex.
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphWB instance (weighted, undirected graph)
	 * Returns:
	 *  - A std::vector, each element being another std::vector (DFSComponent)
	 *    of vertices that are connected (in no particular order)
	 */ 
	template<class T, class W>
	std::vector<DFSComponent<GraphVertexWB<T, W>*>> dfs_cc(const GraphWB<T, W>& g);

	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Runs in listed order.
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphWB instance (weighted, undirected graph)
	 * Returns:
	 *  - A std::vector, each element being an arbitrary vertex in a connected
	 *    component.
	 */ 
	template<class T, class W>
	std::vector<GraphVertexWB<T, W>*> dfs_cc(const GraphWB<T, W>& g, std::initializer_list<GraphVertexWB<T, W>*>& list);

	/*
	 * Perform depth-first search, retaining information about 
	 * post/pre-numbers. Starts on an arbitrary vertex.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphW instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being a vector
	 */ 
	template<class T, class W>
	std::vector<DFSResult<GraphVertexW<T,W>>> dfs_full(const GraphW<T,W>& g);



	template<class T, class W>
	std::vector<DFSComponent<GraphVertexW<T,W>*>> dfs_cc(const GraphW<T, W>& g) {
		std::vector<DFSComponent<GraphVertexW<T,W>*>> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		std::stack<GraphVertexW<T, W>*> work_stack;
		std::unordered_set<GraphVertexW<T, W>*> visited;
		auto iter = g.begin();
		while(iter != g.end()) {
			GraphVertexW<T, W>* vert = iter->second;
			if(visited.find(vert) != visited.end()) {
				work_stack.push(vert);
				DFSComponent<GraphVertexW<T, W>*> component;
				result.push_back(component);
				while(!work_stack.empty()) {
					GraphVertexW<T, W>* vertex = work_stack.top();
					visited.insert(vertex);
					component.push_back(vertex);
					auto iter = vertex->neighbors();
					while(iter != vertex->neighborsEnd()) {
						if(visited.find(iter->first) != visited.end()) {
							work_stack.push(iter->first);
						}
						++iter;
					}
				}
			}
		}
		return result;
	}

	template<class T, class W>
	std::vector<DFSComponent<GraphVertexWB<T, W>*>> dfs_cc(const GraphWB<T, W>& g) {
		std::vector<DFSComponent<GraphVertexWB<T,W>*>> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		std::stack<GraphVertexWB<T, W>*> work_stack;
		std::unordered_set<GraphVertexW<T,W>*> visited;
		for(auto g_vertex : g._vertices) {
			if(visited.find(g_vertex->second) != visited.end()) {
				work_stack.push(g_vertex->second);
				DFSComponent<GraphVertexWB<T,W>*> component;
				result.push_back(component);
				while(!work_stack.empty()) {
					GraphVertexWB<T, W>* vertex = work_stack.top();
					visited.insert(vertex);
					component.push_back(vertex);
					auto iter = vertex->neighbors();
					while(iter != vertex->neighborsEnd()) {
						if(visited.find(iter->second) != visited.end()) {
							work_stack.push(iter->second);
						}
						++iter;
					}
				}
			}
		}
		return result;
	}


}

#endif