#include "graph.hpp"


firenoo::Graph::Graph() {
	this->_edgeCount = 0;
}


firenoo::Graph::~Graph() {
	
}

//READ operations -------------------------------------------------------------


unsigned int firenoo::Graph::vertexCount() const {
	return vertices.size();
}


unsigned int firenoo::Graph::edgeCount() const {
	return this->_edgeCount;
}

//WRITE operations ------------------------------------------------------------