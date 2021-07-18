#ifndef _FN_DISJOINTSET
	#define _FN_DISJOINTSET 0
	#include <vector>
	#include <unordered_map>

namespace firenoo {

/*
 * DisjointSet
 */
class DisjointSet {

public:
	struct Node {
		//parent index
		size_t _parent;
		//rank (max height of node)
		size_t _rank;

		//Default constructor
		Node(size_t parent, size_t rank);

		//Move constructor
		Node(Node&& other);

		//Move assignment
		Node& operator=(Node&& other) noexcept;
		//Copy assignment
		Node& operator=(const Node& other) noexcept;
	};

	//Backing array
	std::vector<Node> _set;

	//Default constructor, creates a disjoint set of size `size`.
	DisjointSet(size_t size) noexcept;

	//Move constructor
	DisjointSet(DisjointSet&& other) noexcept;

	//Finds the observer (root node) of the specified node.
	//Input is the index of the node.
	size_t find(size_t x);

	//Merges the sets that `a` and `b` belong to. Returns
	//true if the merge occurred
	bool merge(size_t a, size_t b);

	//gets the size of the backing array.
	size_t max_size();

	Node& operator[](size_t index);
};

}



#endif