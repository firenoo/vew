#ifndef _FN_DISJOINTSET
	#define _FN_DISJOINTSET 0
	#include <cstddef>
	#include <vector>
	#include <unordered_map>

namespace firenoo {

/*
 * DisjointSet
 */
class DisjointSet {

public:
	class Node final {
	protected:
		friend class DisjointSet;
		//parent index
		std::size_t m_parent;
		//rank (max height of node)
		std::size_t m_rank;
	public:
		//Default constructor
		Node(std::size_t parent, std::size_t rank);

		//Move constructor
		Node(Node&& other);

		std::size_t rank() noexcept;

		std::size_t parent() noexcept;

		//Move assignment
		Node& operator=(Node&& other) noexcept;
		//Copy assignment
		Node& operator=(const Node& other) noexcept;
	};

	//Backing array
	std::vector<Node> m_set;

	//Default constructor, creates a disjoint set of size `size`.
	DisjointSet(std::size_t size) noexcept;

	//Move constructor
	DisjointSet(DisjointSet&& other) noexcept;

	//Finds the observer (root node) of the specified node.
	//Input is the index of the node.
	std::size_t find(std::size_t x);

	//Merges the sets that `a` and `b` belong to. Returns
	//true if the merge occurred
	bool merge(std::size_t a, std::size_t b);

	//gets the size of the backing array.
	std::size_t max_size();

	Node& operator[](std::size_t index);
};

}



#endif