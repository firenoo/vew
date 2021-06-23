#ifndef _FN_SEARCH
	#define _FN_SEARCH 0
	#include <vector>
	#include "graphw.hpp"
	#include "graphwb.hpp"
namespace firenoo {

	/*
	 * The result of DFS searching. Includes pre- and post- numbers. 
	 * 
	 * 
	 * 
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

		Vertex* _value;
	};

	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Starts on an arbitrary vertex.
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphW instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being an arbitrary vertex in a connected
	 *    component.
	 */ 
	template<class T, class W>
	std::vector<GraphVertexW<T, W>*> dfs_cc(GraphW<T, W>& g);

	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Starts on an arbitrary vertex.
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphWB instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being an arbitrary vertex in a connected
	 *    component.
	 */ 
	template<class T, class W>
	std::vector<GraphVertexWB<T, W>*> dfs_cc(GraphWB<T, W>& g);

	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Runs in listed order.
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphW instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being an arbitrary vertex in a connected
	 *    component.
	 */ 
	template<class T, class W>
	std::vector<GraphVertexWB<T, W>*> dfs_cc(GraphWB<T, W>& g, std::initializer_list<GraphVertexWB<T, W>&> list);

}

#endif