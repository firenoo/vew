#include "graph_vertex.hpp"

template<class T>
firenoo::GraphVertex<T>::GraphVertex(const T&& obj) : _indegree(0), _obj(obj) {
	_neighbors = std::unordered_map<GraphVertex<T>*, double>();
}

template<class T>
firenoo::GraphVertex<T>::~GraphVertex() {
	for(auto neighbor : _neighbors) {
		delete neighbor->second;
	}
}


//READ operations -------------------------------------------------------------
//Protected
template<class T>
double firenoo::GraphVertex<T>::getEdge(GraphVertex<T>* const& other) const {
	auto e = _neighbors.find(other);
	return e != _neighbors.end() ? e->second : 0;
}

//Public
template<class T>
const T firenoo::GraphVertex<T>::get() const {
	return _obj;
}

template<class T>
size_t firenoo::GraphVertex<T>::indegree() const {
	return _indegree;
}

template<class T>
size_t firenoo::GraphVertex<T>::outdegree() const {
	return _neighbors.size();
}

template<class T>
bool firenoo::GraphVertex<T>::hasEdge(const GraphVertex<T>* other) const {
	auto weights = _neighbors.find(other);
	return weights != _neighbors.end();
}

//WRITE operations ------------------------------------------------------------

template<class T>
bool firenoo::GraphVertex<T>::addEdge(GraphVertex<T>* other, double weight) {
	//Lazy style - only add an entry if needed.
	if(!hasEdge(other)) {
		_neighbors[other] = weight;
		return true;
	}
	return false;
}

template<class T>
bool firenoo::GraphVertex<T>::removeEdge(GraphVertex<T>* other) {
	if(hasEdge(other)) {
		_neighbors.erase(other);
		return true;
	}
	return false;
}
