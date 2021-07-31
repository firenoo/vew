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

	/*
	 * DFSPostCompare - Comparator for sorting post numbers
	 * V - vertex type
	 * Reverse - whether to sort from smallest to largest (false) or vice versa
	 * (true)
	 */
	template <class GraphVertex, bool Reverse = false>
	struct DFSPostCompare {};

	template <class GraphVertex>
	struct DFSPostCompare<GraphVertex, true> {
		bool operator()(
			std::tuple<std::size_t, std::size_t, GraphVertex>& a, 
			std::tuple<std::size_t, std::size_t, GraphVertex>& b) noexcept {
			return std::get<1>(a) > std::get<1>(b);
		}
	};

	template <class GraphVertex>
	struct DFSPostCompare<GraphVertex, false> {
		bool operator()(
			std::tuple<std::size_t, std::size_t, GraphVertex>& a, 
			std::tuple<std::size_t, std::size_t, GraphVertex>& b) noexcept {
			return std::get<1>(a) < std::get<1>(b);
		}
	};

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
	simpleDFS(const DGraph& g, std::initializer_list<typename DGraph::Vertex*> args);

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
	std::vector<std::tuple<std::size_t, std::size_t, typename DGraph::Vertex*>> 
	fullDFS(const DGraph& g, std::initializer_list<typename DGraph::Vertex*> args);

	/*
	 * Finds whether there is a cycle in the graph.
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
	 * Constructs a topological sort of the graph.
	 * 
	 * READ operation.
	 * Parameters:
	 *  - g : A DirectedGraph instance (weighted, directed graph)
	 * Returns:
	 *  - a topological sort of the graph
	 */
	template<class T, class W, class Hash, class KeyEq>
	std::vector<typename DGraph::Vertex*> topSort(const DGraph& g);

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
		using Vertex = DGraph::Vertex;
		//DFS search loop
		while(!work_stack.empty()) {
			Vertex* vertex = work_stack.top();
			work_stack.pop();
			std::size_t ind = master_map[vertex];
			//Iterate through neighbors
			for(auto it : **vertex) {
				//Look if neighbor was already visited
				size_t it_ind = master_map[it->first];
				//Try to add the neighbor vertex to the visit list, if it isn't
				//already visited. If it hasn't been visited, add it to the
				//stack so we can expand it later.
				//A node is unvisited if we can merge with the current set and
				//is a singleton component.
				if(set[set.find(it_ind)].rank() == 0 && set.merge(it_ind, ind)) {
					//Neighbor not already visited.
					work_stack.push(it->first);
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
	simpleDFS(const DGraph& g, std::initializer_list<typename DGraph::Vertex*>& args) {
		using Vertex = typename DGraph::Vertex;
		std::vector<std::vector<Vertex*>> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		//Initialization
		result.reserve(g.vertexCount());
		DisjointSet work_set(g.vertexCount());
		std::stack<Vertex*> work_stack;
		std::unordered_map<Vertex*, std::size_t> master_map;
		master_map.reserve(g.vertexCount());
		std::size_t i = 0;
		for(auto& const it : g) {
			master_map[it->second] = i; //fill out map
			++i;
		}
		//Handle arguments
		if(args.size() > 0) {
			for(Vertex* v : args) {
				std::size_t v_ind = master_map[v];
				if(work_set.find(v_ind) == v_ind && work_set[v_ind].rank() == 0u) {
					work_stack.push(v);
					dSimpleExplore(work_stack, work_set, master_map);
				}
			}
		}
		//Handle the rest
		for(auto& it : g) {
			Vertex* vert = it->second; //top-level vertex
			std::size_t v_ind = master_map[vert];
			if(work_set.find(v_ind) == v_ind && work_set[v_ind].rank() == 0u) {
				//Start a new DFS tree
				work_stack.push(vert);
				dSimpleExplore(work_stack, work_set, master_map);
			}
		}
		//Construct the result from the disjoint set
		std::unordered_map<size_t, size_t> component_map;
		component_map.reserve(g.vertexCount());
		result.reserve(g.vertexCount());
		size_t ctr = 0;
		for(auto pair : master_map) {
			size_t ind = work_set.find(pair.second);
			if(component_map.find(ind) == component_map.end()) {
				component_map[ind] = ctr++;
				result.push_back(new DComponent());
			}
			result[component_map[ind]]->insert(pair.first);
		}
		result.shrink_to_fit();
		return result;
	}
/*

	template<class T, class W, class Hash, class KeyEq>
	static void dFullExplore(
		std::stack<typename DGraph::Vertex*>& work_stack,
		DisjointSet& set,
		std::unordered_map<typename DGraph::Vertex*, size_t>& master_map,
		size_t& order
	) {
		using Vertex = typename DGraph::Vertex;
		while(!work_stack.empty()) {
			//DFS search loop
			Vertex info = work_stack.top(); //copy?
			Vertex* v = info._vertex;
			// info._pre = order++; //Adjust preorder
			//Expand node
			bool bt = true; //pessimistic backtrack flag

			for(auto it = v->neighbors(); it != v->neighborsEnd(); ++it) {
				if(set.merge(master_map[v], master_map[it->first])) {
					//Neighbor not already visited, add to stack
					work_stack.emplace(0, 0, it->first);
					bt = false;
				}
			}
			if(bt) {
				//There were no options, backtrack
				info._post = order++;
				work_stack.pop();
			} else {
				info._pre = order++;
			}
		}

	}
template<class T, class W>
std::vector<DFullComp*> fullDFS(const DGraph& g, std::initializer_list<DVertex*> args) {
	std::vector<DFullComp*> result;
	if(g.vertexCount() == 0) {
		return result;
	}
	size_t order = 0;
	//data structures
	std::stack<DDFSResult> work_stack;
	DisjointSet work_set(g.vertexCount());
	std::unordered_set<DVertex*> visited;
	std::unordered_map<DVertex*, size_t> master_map;
	//reserve size
	visited.reserve(g.vertexCount());
	result.reserve(g.vertexCount());
	master_map.reserve(g.vertexCount());
	//initialize master map
	size_t i = 0;
	for(auto it = g.begin(); it != g.end(); ++it) {
		master_map[it->second] = i;
		++i;
	}
	//priority order first
	if(args.size() > 0) {
		for(DVertex* v : args) {
			work_stack.emplace(0, 0, v);
		}
		dfs_explore_full(work_stack, work_set, master_map, visited, order);
	}
	//remaining vertices
	for(auto iter = g.begin(); iter != g.end(); ++iter) {
		//Main loop
		DVertex* vert = iter->second; //top-level vertex
		if(visited.find(vert) == visited.end()) {
			//Start a new DFS tree
			work_stack.emplace(order, 0, vert);
			dfs_explore_full(work_stack, work_set, master_map, visited, order);
		}
	}
	result.shrink_to_fit();
	return result;
}

template<class T, class W>
static bool dfs_explore_cycle(std::stack<DVertex*>& work_stack, std::unordered_set<DVertex*>& visited) {
	while(!work_stack.empty()) {
		//DFS search loop
		DVertex* vertex = work_stack.top();
		work_stack.pop();
		if(visited.find(vertex) != visited.end()) continue;
		visited.insert(vertex); //Mark as visited
		//Iterate through neighbors
		auto n = vertex->neighbors();
		while(n != vertex->neighborsEnd()) {
			//Look if neighbor was already visited
			if(visited.find(n->first) == visited.end()) {
				//Expand neighbor
				work_stack.push(n->first);
			} else {
				//Found a cycle
				return true;
			}
			++n;
		}
	}
	return false;
}

template<class T, class W>
bool has_cycle(const DGraph& g) {
	//Strategy: perform dfs from all vertices; if we encounter a vertex
	//that we visited already, we found a cycle
	std::stack<DVertex*> work_stack;
	std::unordered_set<DVertex*> visited;
	auto iter = g.begin();
	while(iter != g.end()) {
		if(visited.find(iter->second) == visited.end()) {
			work_stack.push(iter->second);
			if(dfs_explore_cycle(work_stack, visited)) {
				return true;
			}
		}
		++iter;
	}
	return false;
}

template<class T, class W>
std::vector<DDFSResult> top_sort(const DGraph& g) {
	std::vector<DDFSResult> result;
	result.reserve(g.vertexCount());
	std::vector<DFullComp*> dfs_result = dfs_full(g, {});
	for(DFullComp* c : dfs_result) {
		for(auto iter = c->begin(); iter != c->end(); ++iter) {
			//move all values from the unordered_set to vector
			result.push_back(std::move(c->extract(iter).value()));
		}
	}
	//Sort by post-order
	DFSPostCompare<DVertex, true> cmp;
	std::sort(result.begin(), result.end(), cmp);
	return result;
}


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