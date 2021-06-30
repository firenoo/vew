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
	 *  - g : A GraphW instance (weighted, directed graph)
	 * Returns:
	 *  - A std::vector, each element being another std::vector (a component)
	 *    of vertices that are connected (in no particular order). Note: each
	 *    component std::vector is allocated on the heap; it is the user's
	 *    responsibility to manage it.
	 */ 
	template<class T, class W>
	std::vector<std::unordered_set<GraphVertexW<T, W>*>*> dfs_cc(const GraphW<T, W>& g, std::initializer_list<GraphVertexW<T, W>*> args);
	/*
	 * Perform depth-first search, keeping only information about
	 * connected components. Starts on an arbitrary vertex.
	 * READ operation.
	 * Parameters:
	 *  - g : A GraphWB instance (weighted, undirected graph)
	 * Returns:
	 *  - A std::vector, each element being another std::vector (a component)
	 *    of vertices that are connected (in no particular order)
	 */ 
	template<class T, class W>
	std::vector<std::unordered_set<GraphVertexWB<T, W>*>*> dfs_cc(const GraphWB<T, W>& g, std::initializer_list<GraphVertexWB<T, W>*> args);

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
	// template<class T, class W>
	// std::vector<DFSResult<GraphVertexW<T,W>>> dfs_full(const GraphW<T,W>& g);

	#define Graph GraphW<T, W>
	#define Vertex GraphVertexW<T, W>
	#define Component std::unordered_set<GraphVertexW<T, W>*>

	template<class T, class W>
	void dfs_explore(std::stack<Vertex*>& work_stack, std::unordered_map<Vertex*, Component*>& visited, std::vector<Component*>& result) {
		//"Uptree"
		Component* component = new Component();				
		bool addComponent = true;
		while(!work_stack.empty()) {
			//DFS search loop
			Vertex* vertex = work_stack.top();
			work_stack.pop();
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
				} else if(old_component->second != component) {
					//Neighbor visited already, and is in a different
					//component. Must bridge the two components.
					Component* other = old_component->second;
					//Add all vertices to the larger of the two
					//components, and set it to be the new
					//current component.
					if(other->size() >= component->size()) {
						for(Vertex* v : *component) {
							visited[v] = other;
							other->insert(v);
						}								
						delete component;
						component = other;
						addComponent = false;
					} else {
						for(Vertex* v : *other) {
							visited[v] = component;
							component->insert(v);
						}								
						delete other;
					}
				}
				++n;
			}
		}
		if(addComponent) {
			result.push_back(component);
		}	
	}

	template<class T, class W>
	std::vector<Component*> dfs_cc(const Graph& g, std::initializer_list<Vertex*> args) {
		std::vector<Component*> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		
		std::stack<Vertex*> work_stack;
		std::unordered_map<Vertex*, Component*> visited;
		
		if(args.size() > 0) {
			for(Vertex* v : args) {
				work_stack.push(v);
				dfs_explore(work_stack, visited, result);
			}
		}
		auto iter = g.begin();
		while(iter != g.end()) {
			//Main loop
			Vertex* vert = iter->second; //top-level vertex
			if(visited.find(vert) == visited.end()) {
				//Start a new DFS tree
				work_stack.push(vert);
				dfs_explore(work_stack, visited, result);
			}
			++iter;
		}
		return result;
	}
	#undef Component
	#undef Vertex
	#undef Graph

	#define Graph GraphWB<T, W>
	#define Vertex GraphVertexWB<T, W>
	#define Component std::unordered_set<GraphVertexWB<T, W>*>

	template<class T, class W>
	void dfs_explore(std::stack<Vertex*>& work_stack, std::unordered_map<Vertex*, Component*>& visited, std::vector<Component*>& result) {
		Component* component = new Component();
		while(!work_stack.empty()) {
			//DFS search loop
			Vertex* vertex = work_stack.top();
			work_stack.pop();
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
	std::vector<Component*> dfs_cc(const Graph& g, std::initializer_list<Vertex*> args) {
		std::vector<Component*> result;
		if(g.vertexCount() == 0) {
			return result;
		}
		
		std::stack<Vertex*> work_stack;
		std::unordered_map<Vertex*, Component*> visited;
		
		if(args.size() > 0) {
			for(Vertex* v : args) {
				work_stack.push(v);
				dfs_explore(work_stack, visited, result);
			}
		}
		auto iter = g.begin();
		while(iter != g.end()) {
			//Main loop
			Vertex* vert = iter->second; //top-level vertex
			if(visited.find(vert) == visited.end()) {
				//Start a new DFS tree
				work_stack.push(vert);
				dfs_explore(work_stack, visited, result);
			}
			++iter;
		}
		return result;
	}
	#undef Component
	#undef Vertex
	#undef Graph


}

#endif