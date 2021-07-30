#include "disjointset.hpp"
#include <utility>
namespace firenoo {

DisjointSet::DisjointSet(size_t size) noexcept {
	m_set.reserve(size);
	for(unsigned int i = 0; i < size; ++i) {
		m_set.emplace_back(i, 0);
	}
}

DisjointSet::DisjointSet(DisjointSet&& other) noexcept {
	m_set.insert(m_set.end(), 
	            std::make_move_iterator(other.m_set.begin()),
				std::make_move_iterator(other.m_set.end()));
	other.m_set.erase(other.m_set.begin(), other.m_set.end());
}

size_t DisjointSet::find(size_t x) {
	size_t parent = m_set[x].m_parent;
	for(; parent != x; parent = m_set[x].m_parent) {
		x = m_set[x].m_parent;
	}
	return x;
}

bool DisjointSet::merge(size_t a, size_t b) {
	size_t x = find(a);
	size_t y = find(b);
	if(x == y) {
		return false;
	}

	if(m_set[x].m_rank < m_set[y].m_rank) {
		std::swap(x, y);
	}
	m_set[y].m_parent = x;

	if(m_set[x].m_rank ==m_set[y].m_rank) {
		++m_set[x].m_rank;
	}
	return true;
}

size_t DisjointSet::max_size() {
	return m_set.size();
}

DisjointSet::Node& DisjointSet::operator[](size_t index) {
	return m_set[index];
}

DisjointSet::Node::Node(size_t parent, size_t rank) :
	m_parent(parent),
	m_rank(rank) {}

DisjointSet::Node::Node(Node&& other) :  m_parent(other.m_parent), m_rank(other.m_rank) {}

DisjointSet::Node& DisjointSet::Node::operator=(Node&& other) noexcept {
	if(this != &other) {
		m_parent = other.m_parent;
		m_rank = other.m_rank;
	}
	return *this;
}

DisjointSet::Node& DisjointSet::Node::operator=(const Node& other) noexcept {
	if(this != &other) {
		m_parent = other.m_parent;
		m_rank = other.m_rank;
	}
	return *this;
}
}