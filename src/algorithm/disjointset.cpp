#include "disjointset.hpp"
#include <utility>
namespace firenoo {

DisjointSet::DisjointSet(size_t size) noexcept {
	_set.reserve(size);
	for(unsigned int i = 0; i < size; ++i) {
		_set.emplace_back(i, 0);
	}
}

DisjointSet::DisjointSet(DisjointSet&& other) noexcept {
	_set.insert(_set.end(), 
	            std::make_move_iterator(other._set.begin()),
				std::make_move_iterator(other._set.end()));
	other._set.erase(other._set.begin(), other._set.end());
}

size_t DisjointSet::find(size_t x) {
	size_t parent = _set[x]._parent;
	for(; parent != x; parent = _set[x]._parent) {
		x = _set[x]._parent;
	}
	return x;
}

bool DisjointSet::merge(size_t a, size_t b) {
	size_t x = find(a);
	size_t y = find(b);
	if(x == y) {
		return false;
	}

	if(_set[x]._rank < _set[y]._rank) {
		std::swap(x, y);
	}
	_set[y]._parent = x;

	if(_set[x]._rank ==_set[y]._rank) {
		++_set[x]._rank;
	}
	return true;
}

size_t DisjointSet::max_size() {
	return _set.size();
}

DisjointSet::Node& DisjointSet::operator[](size_t index) {
	return _set[index];
}

DisjointSet::Node::Node(size_t parent, size_t rank) :
	_parent(parent),
	_rank(rank) {}

DisjointSet::Node::Node(Node&& other) :  _parent(other._parent), _rank(other._rank) {}

DisjointSet::Node& DisjointSet::Node::operator=(Node&& other) noexcept {
	if(this != &other) {
		_parent = other._parent;
		_rank = other._rank;
	}
	return *this;
}

DisjointSet::Node& DisjointSet::Node::operator=(const Node& other) noexcept {
	if(this != &other) {
		_parent = other._parent;
		_rank = other._rank;
	}
	return *this;
}
}