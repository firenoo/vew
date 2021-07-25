#ifndef _FN_SEARCH
	#define _FN_SEARCH 0
	#define _FN_RESERVE_FACTOR 2
	#include <cstdint>
	#include <vector>
	#include <stack>
	#include <algorithm>
	#include "udigraph.hpp"
	#include "digraph.hpp"
	#include "disjointset.hpp"
	//Directed Graph
	#define DGraph DirectedGraph<T, W>
	//Directed Graph Vertex
	#define DVertex GraphVertexW<T, W>
	//Directed Graph Component
	#define DComponent std::unordered_set<GraphVertexW<T, W>*>
	//Directed Graph DFS Component
	#define DFullComp std::unordered_set<DFSResult<GraphVertexW<T, W>>, DFSHash<GraphVertexW<T, W>>>
	//Directed Graph DFS Result
	#define DDFSResult DFSResult<GraphVertexW<T, W>>


	//Undirected Graph
	#define UGraph UndirectedGraph<T, W>
	#define UVertex GraphVertexWB<T, W>
	#define UComponent std::unordered_set<GraphVertexWB<T, W>*>
	#define UFullComp std::unordered_set<DFSResult<GraphVertexWB<T, W>>, DFSHash<GraphVertexWB<T, W>>>
	#define UDFSResult DFSResult<GraphVertexWB<T, W>>

namespace firenoo {

//-----------------------------------------------------------------------------
// DFS Result processing
//-----------------------------------------------------------------------------


/*
	* The result of DFS searching. Includes pre- and post- numbers. 
	*/
template<typename V>
struct DFSResult {
	
	//Default constructor
	DFSResult(size_t pre, size_t post, V* vertex) : 
		_pre(pre), 
		_post(post),
		_vertex(vertex) {}
	
	//Copy constructor
	DFSResult(const DFSResult& other) :
		_pre(other._pre),
		_post(other._post),
		_vertex(other._vertex) {}
	
	//Move constructor
	DFSResult(DFSResult&& other) {
		_pre = other._pre;
		_post = other._post;
		_vertex = other._vertex;

		other._vertex = nullptr;
	}

	/*
		* Pre-numbering
		*/
	size_t _pre = 0;

	/*
		* Post-numbering
		*/
	size_t _post = 0;

	/*
		* Vertex. Do not delete, as we do not own this pointer.
		*/
	V* _vertex = nullptr;

	//Copy assignment
	DFSResult& operator=(const DFSResult<V>& other) noexcept {
		if(this != &other) {
			_pre = other._pre;
			_post = other._post;
			_vertex = other._vertex;
		}
		return *this;
	}

	//Move assignment
	DFSResult& operator=(DFSResult<V>&& other) noexcept {
		if(this != &other) {
			_pre = other._pre;
			_post = other._post;
			_vertex = other._vertex;

			other._pre = 0;
			other._post = 0;
			other._vertex = nullptr;
		}
		return *this;
	}

	//Equivalence operator
	bool operator==(const DFSResult<V>& b) const noexcept {
		return _pre == b._pre && _post == b._post && _vertex == b._vertex;
	}

};

/*
	* DFSPostCompare - Comparator for sorting post numbers
	* V - vertex type
	* Reverse - whether to sort from smallest to largest (false) or vice versa
	* (true)
	*/
template <class V, bool Reverse = false>
struct DFSPostCompare {};

template <class V>
struct DFSPostCompare<V, true> {
	bool operator()(DFSResult<V>& a, DFSResult<V>& b) noexcept {
		return a._post > b._post;
	}
};

template<class V>
struct DFSPostCompare<V, false> {
	bool operator()(const DFSResult<V>& a, const DFSResult<V>& b) const noexcept {
		return a._post < b._post;
	}
};

/*
	* DFSHash - class for creating a hash value for DFSResult.
	*/
template<class V>
struct DFSHash {
	size_t operator()(const DFSResult<V>& d) const noexcept {
		return ((d._pre ^ reinterpret_cast<std::uintptr_t>(d._vertex) ) << 32) | 
				(d._post ^ reinterpret_cast<std::uintptr_t>(d._vertex));
	}
};

	

//-----------------------------------------------------------------------------
// Directed Graph
//-----------------------------------------------------------------------------

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
	*    of vertices that are connected (in no particular order). Note: each
	*    component std::vector is allocated on the heap; it is the user's
	*    responsibility to manage it.
	*/ 
template<class T, class W>
std::vector<DComponent*> dfs_cc(const DGraph& g);

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
	*    of vertices that are connected (in no particular order). Note: each
	*    component std::vector is allocated on the heap; it is the user's
	*    responsibility to manage it.
	*/ 
template<class T, class W>
std::vector<DComponent*> dfs_cc(const DGraph& g, std::initializer_list<DVertex*> args);

/*
	* Perform depth-first search, retaining information about 
	* post/pre-numbers. Starts on an arbitrary vertex.
	* 
	* READ operation.
	* Parameters:
	*  - g : A DirectedGraph instance (weighted, directed graph)
	* Returns:
	*  - A std::vector, each element being a vector
	*/ 
template<class T, class W>
std::vector<DFullComp*> dfs_full(const DGraph& g, std::initializer_list<DVertex*> args);



/*
	* Finds whether there is a cycle in the graph.
	*
	* READ operation.
	* Parameters:
	*  - g : A DirectedGraph instance (weighted, directed graph)
	* Returns:
	*  - true if and only if there exists a cycle in the graph
	*/
template<class T, class W>
bool has_cycle(const DGraph& g);

/*
	* Returns a topological sort of the graph.
	*
	* READ operation.
	* Parameters:
	*  - g : A DirectedGraph instance (weighted, directed graph)
	* Returns:
	*  - true if and only if there exists a cycle in the graph
	*/
template<class T, class W>
std::vector<DDFSResult> top_sort(const DGraph& g);

//-----------------------------------------------------------------------------
// Undirected Graphs
//-----------------------------------------------------------------------------

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
template<class T, class W>
std::vector<UComponent*> dfs_cc(const UGraph& g, std::initializer_list<UVertex*> args);

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
template<class T, class W>
std::vector<UFullComp*> dfs_full(const UGraph& g, std::initializer_list<UVertex*> args);

//-----------------------------------------------------------------------------

// Directed Graphs

//Helper function. Executes DFS with the element(s) contained in `work_stack`.
template<class T, class W>
static void dfs_explore(
	std::stack<DVertex*>& work_stack,
	DisjointSet& set,
	std::unordered_map<DVertex*, size_t>& master_map
) {
	//DFS search loop
	while(!work_stack.empty()) {
		DVertex* vertex = work_stack.top();
		work_stack.pop();
		size_t ind = master_map[vertex];
		//Iterate through neighbors
		for(auto it = vertex->neighbors(); it != vertex->neighborsEnd(); ++it) {
			//Look if neighbor was already visited
			size_t it_ind = master_map[it->first];
			//Try to add the neighbor vertex to the visit list, if it isn't
			//already visited. If it hasn't been visited, add it to the
			//stack so we can expand it later.
			//A node is unvisited if we can merge with the current set and
			//is a singleton component.
			if(set[set.find(it_ind)]._rank == 0 && set.merge(it_ind, ind)) {
				//Neighbor not already visited.
				work_stack.push(it->first);
			}
		}
	}
}

template<class T, class W>
std::vector<DComponent*> dfs_cc(
	const DGraph& g, 
	std::initializer_list<DVertex*> args
) {
	std::vector<DComponent*> result;
	if(g.vertexCount() == 0) {
		return result;
	}
	result.reserve(g.vertexCount() / _FN_RESERVE_FACTOR);
	DisjointSet work_set(g.vertexCount());
	std::stack<DVertex*> work_stack;
	std::unordered_map<DVertex*, size_t> master_map;
	master_map.reserve(g.vertexCount());
	size_t i = 0;
	for(auto it = g.begin(); it != g.end(); ++it) {
		master_map[it->second] = i;
		++i;
	}
	if(args.size() > 0) {
		//Handling arguments
		for(DVertex* v : args) {
			work_stack.push(v);
		}
		dfs_explore(work_stack, work_set, master_map);
	}
	for(auto it = g.begin(); it != g.end(); ++it) {
		//Main loop
		DVertex* vert = it->second; //top-level vertex
		size_t v_ind = master_map[vert];
		if(work_set.find(v_ind) == v_ind && work_set[v_ind]._rank == 0u) {
			//Start a new DFS tree
			work_stack.push(vert);
			dfs_explore(work_stack, work_set, master_map);
		}
	}
	std::unordered_map<size_t, size_t> component_map;
	component_map.reserve(g.vertexCount());
	result.reserve(g.vertexCount());
	
	size_t ctr = 0;
	//Construct results
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

template<class T, class W>
std::vector<DComponent*> dfs_cc(const DGraph& g) {
	return dfs_cc(g, {});
}

template<class T, class W>
static void dfs_explore_full(
	std::stack<DDFSResult>& work_stack,
	DisjointSet& set,
	std::unordered_map<DVertex*, size_t>& master_map,
	std::unordered_set<DVertex*> visited,
	size_t& order
) {
	while(!work_stack.empty()) {
		//DFS search loop
		DDFSResult info = work_stack.top(); //copy?
		DVertex* v = info._vertex;
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
std::vector<DFullComp*> dfs_full(const DGraph& g, std::initializer_list<DVertex*> args) {
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
	#undef DGraph 
	#undef DVertex 
	#undef DComponent 
	#undef DFullComp 
	#undef DDFSResult

	#undef UGraph 
	#undef UVertex 
	#undef UComponent 
	#undef UFullComp 
	#undef UDFSResult
}

#endif