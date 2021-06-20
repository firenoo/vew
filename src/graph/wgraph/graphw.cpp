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

//WRITE operations ------------------------------------------------------------

