#include "graphw.hpp"

template<class T>
firenoo::GraphW<T>::GraphW() {
	this->_edgeCount = 0;
}

template<class T>
firenoo::GraphW<T>::~GraphW() {
	clear();
}

//READ operations -------------------------------------------------------------

template<class T>
unsigned int firenoo::GraphW<T>::vertexCount() const {
	return _vertices.size();
}


template<class T>
unsigned int firenoo::GraphW<T>::edgeCount() const {
	return this->_edgeCount;
}

template<class T>
bool firenoo::GraphW<T>::hasVertex(const T& v) const {
	return _vertices.find(v) != _vertices.end();
}

template<class T>
bool firenoo::GraphW<T>::hasEdge(const T& v1, const T& v2) const {
	auto v1 = _vertices.find(v1);
	return v1 != _vertices.end() && v1->second.hasEdge(v2);
}

//WRITE operations ------------------------------------------------------------

template<class T>
firenoo::GraphVertex<T>* firenoo::GraphW<T>::addVertex(const T& id) {
	auto v = _vertices.find(id);
	if(v == _vertices.end()) {
		firenoo::GraphVertex<T> vertex = new firenoo::GraphVertex<T>(id);
		_vertices[id] = vertex;
		return vertex;
	}
	return v->second;
}

template<class T>
bool firenoo::GraphW<T>::addVertex(const GraphVertex<T>* v) {
	if(!hasVertex(v->get())) {
		_vertices[v->get()] = v;
		return true;
	}
	return false;
}

template<class T>
firenoo::GraphVertex<T>* firenoo::GraphW<T>::removeVertex(const T& id) {
	auto v = _vertices.find(id);
	if(v == _vertices.end()) {
		return nullptr;
	}
	_vertices.erase(v);
	return v->second;
}

template<class T>
bool firenoo::GraphW<T>::removeVertex(const GraphVertex<T>* v) {
	auto vertex = _vertices.find(v->get());
	if(vertex != _vertices.end()) {
		_vertices.erase(vertex);
		delete vertex->second;
		return true;
	}
	return false;
}

template<class T>
bool firenoo::GraphW<T>::addEdge(const T& v1, const T& v2, double w) {
	GraphVertex<T> src = addVertex(v1);
	GraphVertex<T> snk = addVertex(v2);
	return src.addEdge(snk, w);
}

template<class T>
bool firenoo::GraphW<T>::removeEdge(const T& v1, const T& v2) {
	auto src = _vertices.find(v1);
	auto snk = _vertices.find(v2);
	if(src != _vertices.end() && snk != _vertices.end()) {
		return vertex->second.removeEdge(snk);
	}
	return false;
}

template<class T>
void firenoo::GraphW<T>::removeAllNeighbors(const T& v) {
	auto query = _vertices.find(v);
	if(query != _vertices.end()) {
		GraphVertex<T>* vertex = query->second;
		vertex->_neighbors.clear();
	}
}

template<class T>
void firenoo::GraphW<T>::clear() {
	for(auto v : _vertices) {
		delete v->second;
		_vertices.erase(v);
	}
}