#ifndef _FN_SEARCH
	#define _FN_SEARCH
	#define _FN_RESERVE_FACTOR 2
	#include <cstddef>
	#include <vector>
	#include <stack>
	#include <tuple>
	#include <algorithm>
	#include "udigraph.hpp"
	#include "digraph.hpp"
	#include "disjointset.hpp"

namespace firenoo {

//-----------------------------------------------------------------------------
// Directed Graph operations
//-----------------------------------------------------------------------------
	#define DGraph DirectedGraph<T, W, Hash, KeyEq>
	/*
	 * Perform depth-first search, keeping only information about
	 * connected components.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being another std::vector (a component)
	 *    of vertices that are connected (in no particular order).
	 */
	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<typename DGraph::Vertex*>> 
	simpleDFS(const DGraph& g);

	/*
	 * Perform depth-first search, keeping only information about
	 * connected components.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being another std::vector (a component)
	 *    of vertices that are connected (in no particular order).
	 */ 
	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<typename DGraph::Vertex*>> 
	simpleDFS(const DGraph& g, std::initializer_list<T> args);

	/*
	 * Perform depth-first search, retaining information about 
	 * post/pre-numbers. Starts on an arbitrary vertex.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector with each element being another vector of tuples. Each
	 *    tuple vector is a component, and each tuple contains the following:
	 *      <0> Pre order number
	 *      <1> Post order number
	 *      <2> Vertex pointer.
	 */ 
	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<std::tuple<std::size_t, std::size_t, typename DGraph::Vertex*>>>
	fullDFS(const DGraph& g);

	/*
	 * Perform depth-first search, retaining information about 
	 * post/pre-numbers. Starts on an arbitrary vertex.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being a vector
	 */ 
	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<std::tuple<std::size_t, std::size_t, typename DGraph::Vertex*>>> 
	fullDFS(const DGraph& g, std::initializer_list<T> args); 

	/*
	 * Finds whether there is a cycle in the graph.
	 *
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - true if and only if there exists a cycle in the graph
	 */
	template<class T, class W, class Hash, class KeyEq>
	bool hasCycle(const DGraph& g);

	/*
	 * Finds whether there is a cycle in the graph.
	 *
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - true if and only if there exists a cycle in the graph
	 */
	template<class T, class W, class Hash, class KeyEq>
	bool hasCycle(const DGraph& g, std::initializer_list<T> args);
	
	/*
	 * Finds the vertices that are parts of a cycle.
	 * Vertices found may be part of multiple cycles, and will be included in
	 * multiple `std::vector`'s as expected.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance
	 * Returns:
	 *   - A `std::vector` that contains `std::vector`'s, each of which
	 *     represent a single cycle.
	 */
	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<typename DGraph::Vertex*>> 
	findCycles(const DGraph& g);

	/*
	 * Finds the vertices that are parts of a cycle.
	 * Vertices found may be part of multiple cycles, and will be included in
	 * multiple `std::vector`'s as expected.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance
	 * Returns:
	 *   - A `std::vector` that contains `std::vector`'s, each of which
	 *     represent a single cycle.
	 */
	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<typename DGraph::Vertex*>> 
	findCycles(const DGraph& g, std::initializer_list<T> args);

	/*
	 * Constructs a topological sort of the graph.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - a topological sort of the graph
	 */
	template<class T, class W, class Hash, class KeyEq>
	std::vector<typename DGraph::Vertex*> topSort(const DGraph& g);

	/*
	 * Constructs a topological sort of the graph.
	 * 
	 * Passing in vertices will suggest the order to run the search in.
	 * Invalid vertices (e.g. vertices that don't belong to the graph) are
	 * ignored/skipped, and remaining vertices are run in arbitrary order.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - a topological sort of the graph
	 */
	template<class T, class W, class Hash, class KeyEq>
	std::vector<typename DGraph::Vertex*> 
	topSort(const DGraph& g, std::initializer_list<T> args);

//-----------------------------------------------------------------------------
// Undirected Graphs
//-----------------------------------------------------------------------------
	#define UGraph UndirectedGraph<T, W, Hash, KeyEq>
	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Starts on an arbitrary vertex.
	 * READ operation.
	 * Parameters:
	 *  - g : A UndirectedGraph instance (weighted, undirected graph)
	 * Returns:
	 *  - A std::vector, each element being another std::vector (a component)
	 *    of vertices that are connected (in no particular order)
	 */ 
	// template<class T, class W, class Hash, class KeyEq>
	// std::vector<std::vector<typename UGraph::Vertex*>> 
	// simpleDFS(const UGraph& g, std::initializer_list<typename UGraph::Vertex*> args);

	/*
	 * Perform depth-first search, retaining information about 
	 * post/pre-numbers. Starts on an arbitrary vertex.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : An UndirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being a vector
	 */ 
	// template<class T, class W, class Hash, class KeyEq>
	// std::vector<std::vector<typename UGraph::Vertex*>> 
	// fullDFS(const UGraph& g, std::initializer_list<typename UGraph::Vertex*> args);

//-----------------------------------------------------------------------------

// Directed Graphs

namespace {

	/*
	 * DFSResult - stores relevant information about dfs, during traversal.
	 */
	struct DFSResult {
		std::size_t m_id, m_pre, m_post;
		bool m_visited, m_expanded;
	};

	template<class T, class W, class Hash, class KeyEq>
	struct PostCompareReverse {
		bool operator()(
			const std::pair<typename DGraph::Vertex*, std::size_t>& a,
			const std::pair<typename DGraph::Vertex*, std::size_t>& b
		) {
			return std::get<1>(a) > std::get<1>(b);
		}
	};


	/*
	 * CycleResult - stores cycle information 
	 */
	struct CycleResult {
		bool m_expanded, m_visited, m_dead;
	};
}
	/* 
	 * Helper function. Executes DFS with the element contained in `work_stack`.
	 * Calling this function with more than one element in the provided stack
	 * will cause undefined behavior.
	 */
	template<class T, class W, class Hash, class KeyEq>
	static void dSimpleExplore(
		std::stack<typename DGraph::Vertex*>& work_stack,
		DisjointSet& set,
		std::unordered_map<typename DGraph::Vertex*, std::size_t>& master_map
	) {
		using V = typename DirectedGraph<T, W, Hash, KeyEq>::Vertex;
		//DFS search loop
		while(!work_stack.empty()) {
			V* vertex = work_stack.top();
			work_stack.pop();
			std::size_t ind = master_map[vertex];
			//Iterate through neighbors
			for(auto it : *vertex) {
				//Look if neighbor was already visited
				std::size_t it_ind = master_map[it.target()];
				//Try to add the neighbor vertex to the visit list, if it isn't
				//already visited. If it hasn't been visited, add it to the
				//stack so we can expand it later.
				//A node is unvisited if we can merge with the current set and
				//is a singleton component. 
				bool isSingleton = set[set.find(it_ind)].rank() == 0;
				bool merged = set.merge(it_ind, ind);
				if(isSingleton && merged) {
					//Neighbor not already visited.
					work_stack.push(it.target());
				}
			}
		}
	}

	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<typename DGraph::Vertex*>> 
	simpleDFS(const DGraph& g) {
		return simpleDFS(g, {});
	}

	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<typename DGraph::Vertex*>> 
	simpleDFS(const DGraph& g, std::initializer_list<T> args) {
		using V = typename DGraph::Vertex;
		std::vector<std::vector<V*>> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		//Initialization
		result.reserve(g.vertexCount());
		DisjointSet work_set(g.vertexCount());
		std::stack<V*> work_stack;
		std::unordered_map<V*, std::size_t> master_map;
		master_map.reserve(g.vertexCount());
		std::size_t i = 0;
		
		for(auto const& it : g) {
			master_map[it.second.get()] = i; //fill out map
			++i;
		}
		//Handle arguments
		for(auto& v : args) {
			if(g.m_vertices.find(v) == g.m_vertices.end()) {
				continue;
			}
			std::size_t v_ind = master_map[g.m_vertices.at(v).get()];
			if(work_set.find(v_ind) == v_ind && work_set[v_ind].rank() == 0u) {
				work_stack.push(g.m_vertices.at(v).get());
				dSimpleExplore<T, W, Hash, KeyEq>(work_stack, work_set, master_map);
			}
		}
		//Handle the rest
		for(auto const& it : g) {
			V* vert = it.second.get(); //top-level vertex
			std::size_t v_ind = master_map[vert];
			if(work_set.find(v_ind) == v_ind && work_set[v_ind].rank() == 0u) {
				//Start a new DFS tree
				work_stack.push(vert);
				dSimpleExplore<T, W, Hash, KeyEq>(work_stack, work_set, master_map);
			}
		}
		//Construct the result from the disjoint set
		std::unordered_map<size_t, size_t> component_map;
		component_map.reserve(g.vertexCount());
		result.reserve(g.vertexCount());
		std::size_t ctr = 0;
		for(auto& pair : master_map) {
			std::size_t ind = work_set.find(pair.second);
			if(component_map.find(ind) == component_map.end()) {
				component_map[ind] = ctr++;
				result.emplace_back();
			}
			result[component_map[ind]].push_back(pair.first);
		}
		for(auto& r : result) {
			r.shrink_to_fit();
		}
		result.shrink_to_fit();
		return result;
	}


	template<class T, class W, class Hash, class KeyEq>
	static void dFullExplore(
		std::stack<typename DGraph::Vertex*>& work_stack,
		DisjointSet& set,
		std::unordered_map<typename DGraph::Vertex*, DFSResult>& master_map,
		size_t& order
	) {
		using V = typename DGraph::Vertex;
		while(!work_stack.empty()) {
			//DFS search loop
			V* vertex = work_stack.top(); //copy?
			//Expand node
			bool bt = true; //pessimistic backtrack flag
			master_map[vertex].m_visited = true;
			if(!master_map[vertex].m_expanded) {
				master_map[vertex].m_pre = order++;
				master_map[vertex].m_expanded = true;
				for(auto& neighbor : *vertex) {
					bool isMerged = set.merge(
						master_map[vertex].m_id, 
						master_map[neighbor.target()].m_id
					);
					if(!master_map[neighbor.target()].m_visited && isMerged) {
						//Neighbor not already visited, add to stack
						work_stack.push(neighbor.target());
						//Keep only 1 instance in the stack
						master_map[neighbor.target()].m_visited = true;
						bt = false;
					}
				}
			}
			if(bt) {
				//There were no options, backtrack
				master_map[vertex].m_post = order++;
				work_stack.pop();
			}
		}

	}

	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<std::tuple<std::size_t, std::size_t, typename DGraph::Vertex*>>> 
	fullDFS(const DGraph& g) {
		return fullDFS(g, {});
	}

	template<class T, class W, class Hash, class KeyEq>
	std::vector<std::vector<std::tuple<std::size_t, std::size_t, typename DGraph::Vertex*>>> 
	fullDFS(const DGraph& g, std::initializer_list<T> args) {
		using V = typename DGraph::Vertex;
		std::vector<std::vector<std::tuple<std::size_t, std::size_t, V*>>> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		size_t order = 0;
		//data structures
		std::stack<V*> work_stack;
		DisjointSet work_set(g.vertexCount());
		std::unordered_map<V*, DFSResult> master_map;
		//reserve size
		result.reserve(g.vertexCount());
		master_map.reserve(g.vertexCount());
		//initialize master map
		size_t i = 0;
		for(auto it = g.begin(); it != g.end(); ++it) {
			master_map[it->second.get()] = {i, 0, 0, false, false};
			++i;
		}
		//priority order first
		for(auto& v : args) {
			if(g.m_vertices.find(v) == g.m_vertices.end()) {
				continue;
			}
			V* vert = g.m_vertices.at(v).get(); //top-level vertex
			if(!master_map[vert].m_visited) {
				work_stack.push(vert);
				dFullExplore<T, W, Hash, KeyEq>(work_stack, work_set, master_map, order);
			}
		}

		//remaining vertices
		for(auto& it : g) {
			//Main loop
			V* vert = it.second.get(); //top-level vertex
			if(!master_map[vert].m_visited) {
				work_stack.push(vert);
				dFullExplore<T, W, Hash, KeyEq>(work_stack, work_set, master_map, order);
			}
		}
		//Construct result

		//Construct the result from the disjoint set
		std::unordered_map<size_t, size_t> component_map;
		component_map.reserve(g.vertexCount());
		result.reserve(g.vertexCount());
		std::size_t ctr = 0;
		for(auto& [vertex, dfsResult] : master_map) {
			std::size_t ind = work_set.find(dfsResult.m_id);
			if(component_map.find(ind) == component_map.end()) {
				component_map[ind] = ctr++;
				result.emplace_back();
			}
			result[component_map[ind]].emplace_back(
				dfsResult.m_pre,
				dfsResult.m_post,
				vertex
			);
		}
		for(auto& r : result) {
			r.shrink_to_fit();
		}

		result.shrink_to_fit();
		return result;
	}

	template<class T, class W, class Hash, class KeyEq>
	static bool dHasCycle(
		std::stack<typename DGraph::Vertex*>& work_stack,
		std::unordered_map<typename DGraph::Vertex*, CycleResult>& master_map
	) {
		using V = typename DGraph::Vertex;
		while(!work_stack.empty()) {
			//DFS search loop
			V* vertex = work_stack.top(); //copy?
			//Expand node
			bool bt = true; //pessimistic backtrack flag
			master_map[vertex].m_visited = true;
			if(!master_map[vertex].m_expanded) {
				master_map[vertex].m_expanded = true;
				for(auto& neighbor : *vertex) {
					if(!master_map[neighbor.target()].m_dead) {
						//Found a cycle!
						return true;
					} else if(!master_map[neighbor.target()].m_visited) {
						//Neighbor not already visited, add to stack
						work_stack.push(neighbor.target());
						//Keep only 1 instance in the stack
						master_map[neighbor.target()].m_visited = true;
						bt = false;
					}
				}
			}
			if(bt) {
				//There were no options, backtrack
				master_map[vertex].m_dead = true;
				work_stack.pop();
			}
		}
		return false;
	}

	template<class T, class W, class Hash, class KeyEq>
	bool hasCycle(const DGraph& g) {
		return hasCycle(g, {});
	}

	template<class T, class W, class Hash, class KeyEq>
	bool hasCycle(const DGraph& g, std::initializer_list<T> args) {
		using V = typename DGraph::Vertex;
		//Strategy: perform dfs from all vertices; if we encounter a vertex
		//that we visited already, we found a cycle
		std::stack<V*> work_stack;
		std::unordered_map<V*, CycleResult> master_map;
		
		master_map.reserve(g.vertexCount());

		for(auto& [obj, v] : g) {
			master_map[v.get()] = {false, false, false};
		}
		for(auto& v : args) {
			if(g.m_vertices.find(v) == g.m_vertices.end()) {
				continue;
			}
			if(!master_map[g.m_vertices.at(v).get()].m_visited) {
				work_stack.push(g.m_vertices.at(v).get());
				if(dHasCycle<T, W, Hash, KeyEq>(work_stack, master_map)) {
					return true;
				}
			}
			//run dfs
		}
		for(auto& [obj, v] : g) {
			//run dfs
			if(!master_map[v.get()].m_visited) {
				work_stack.push(v.get());
				if(dHasCycle<T, W, Hash, KeyEq>(work_stack, master_map)) {
					return true;
				}
			}
		}
		return false;
	}

	template<class T, class W, class Hash, class KeyEq>
	std::vector<typename DGraph::Vertex*> topSort(const DGraph& g) {
		return topSort(g, {});
	}
	
	template<class T, class W, class Hash, class KeyEq>
	std::vector<typename DGraph::Vertex*> topSort(const DGraph& g, std::initializer_list<T> args) {
		using V = typename DGraph::Vertex;
		std::vector<V*> result; 
		//If there's a cycle, return empty.
		if(g.vertexCount() == 0 || hasCycle(g, args)) {
			return result;
		}
		DisjointSet work_set(g.vertexCount());	
		std::stack<V*> work_stack;
		std::unordered_map<V*, DFSResult> master_map;
		std::size_t order = 0;
		master_map.reserve(g.vertexCount());
		result.reserve(g.vertexCount());

		size_t i = 0;
		for(auto it = g.begin(); it != g.end(); ++it) {
			master_map[it->second.get()] = {i, 0, 0, false, false};
			++i;
		}
		//priority order first
		for(auto& v : args) {
			if(g.m_vertices.find(v) == g.m_vertices.end()) {
				continue;
			}
			V* vert = g.m_vertices.at(v).get(); //top-level vertex
			if(!master_map[vert].m_visited) {
				work_stack.push(vert);
				dFullExplore<T, W, Hash, KeyEq>(work_stack, work_set, master_map, order);
			}
		}

		//remaining vertices
		for(auto& it : g) {
			//Main loop
			V* vert = it.second.get(); //top-level vertex
			if(!master_map[vert].m_visited) {
				work_stack.push(vert);
				dFullExplore<T, W, Hash, KeyEq>(work_stack, work_set, master_map, order);
			}
		}
		//Construct result with a temporary vector
		std::vector<std::pair<V*, std::size_t>> temp_result;
		for(auto& [vertex, entry] : master_map) {
			temp_result.emplace_back(vertex, entry.m_post);
		}
		std::sort(temp_result.begin(), temp_result.end(), PostCompareReverse<T, W, Hash, KeyEq>());
		for(auto& r : temp_result) {
			result.push_back(std::get<0>(r));
		}
		return result;
	}
/*

//-----------------------------------------------------------------------------
// Undirected Graphs


	template<class T, class W>
	static void dfs_explore(std::stack<UVertex*>& work_stack, std::unordered_map<UVertex*, UComponent*>& visited, std::vector<UComponent*>& result) {
		UComponent* component = new UComponent();
		while(!work_stack.empty()) {
			//DFS search loop
			UVertex* vertex = work_stack.top();
			work_stack.pop();
			if(visited.find(vertex) != visited.end()) continue;
			visited[vertex] = component; //Mark as visited
			component->insert(vertex); //Add vertex to component
			//Iterate through neighbors
			auto n = vertex->neighbors();
			while(n != vertex->neighborsEnd()) {
				//Look if neighbor was already visited
				auto old_component = visited.find(n->first);
				if(old_component == visited.end()) {
					//Neighbor not already visited
					work_stack.push(n->first);
				}
				++n;
			}
		}
		result.push_back(component);
	}
	template<class T, class W>
	std::vector<UComponent*> dfs_cc(const UGraph& g, std::initializer_list<UVertex*> args) {
		std::vector<UComponent*> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		
		std::stack<UVertex*> work_stack;
		std::unordered_map<UVertex*, UComponent*> visited;
		
		if(args.size() > 0) {
			for(UVertex* v : args) {
				if(!g.hasVertex(v->get())) continue;
				work_stack.push(v);
				dfs_explore(work_stack, visited, result);
			}
		}
		auto iter = g.begin();
		while(iter != g.end()) {
			//Main loop
			UVertex* vert = iter->second; //top-level vertex
			if(visited.find(vert) == visited.end()) {
				//Start a new DFS tree
				work_stack.push(vert);
				dfs_explore(work_stack, visited, result);
			}
			++iter;
		}
		return result;
	}

	template<class T, class W>
	static void dfs_explore_full(std::stack<UDFSResult>& work_stack, std::unordered_map<UVertex*, UFullComp*>& visited, std::vector<UFullComp>& result, size_t& order) {
		//"Uptree"
		UFullComp* component = new UFullComp();				
		bool addComponent = true;
		while(!work_stack.empty()) {
			//DFS search loop
			UDFSResult info = work_stack.top(); //copy?
			UVertex* v = info._vertex;
			if(visited.find(v) != visited.end()) {
				//We've already visited this vertex; it's either
				//already in the stack or in the result.
				work_stack.pop();
				continue;
			}
			info._pre = order++; //Adjust preorder
			visited[v] = component; //Mark as visited
			//Expand node
			bool bt = true; //pessimistic backtrack flag
			auto n = v->neighbors();
			while(n != v->neighborsEnd()) {
				//Look if neighbor was already visited
				auto old_component = visited.find(v);
				if(old_component == visited.end()) {
					//Neighbor not already visited, add to stack
					work_stack.emplace(0, 0, old_component->first);
					bt = false;
				}
				++n;
			}
			if(bt) {
				//Dead end, backtrack
				info._post = order++;
				component->insert(std::move(info)); //insert at the end.
				work_stack.pop();
			}
		}
		if(addComponent) {
			result.push_back(component);
		}
	}

	template<class T, class W>
	std::vector<UFullComp*> dfs_full(const UGraph& g, std::initializer_list<GraphVertexW<T, W>*> args) {
		std::vector<UFullComp*> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		size_t order = 0;
		std::stack<UDFSResult*> work_stack;
		std::unordered_map<UVertex*, UFullComp*> visited;
		
		if(args.size() > 0) {
			for(UVertex* v : args) {
				if(!g.hasVertex(v->get()) || visited.find(v) != visited.end()) continue;
				work_stack.emplace(0, 0, v);
				dfs_explore_full(work_stack, visited, result, order);
			}
		}
		auto iter = g.begin();
		while(iter != g.end()) {
			//Main loop
			UDFSResult* vert = iter->second; //top-level vertex
			if(visited.find(vert) == visited.end()) {
				//Start a new DFS tree
				work_stack.push(vert);
				dfs_explore_full(work_stack, visited, result, order);
			}
			++iter;
		}
		return result;
	}
*/
}
#undef UGraph
#undef DGraph
#endif