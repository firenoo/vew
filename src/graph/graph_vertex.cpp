#include "graph_vertex.hpp"

firenoo::GraphVertex::GraphVertex(const std::string obj) : _indegree(0), _name(obj) {

}

firenoo::GraphVertex::~GraphVertex() {
	
}


//READ operations -------------------------------------------------------------
const std::string& firenoo::GraphVertex::get() const {
	return _name;
}

size_t firenoo::GraphVertex::indegree() const {
	return _indegree;
}

size_t firenoo::GraphVertex::outdegree() const {
	return _edges.size();
}

bool firenoo::GraphVertex::isNeighboring(const GraphVertex* other) const {
	return _edges.find(const_cast<GraphVertex*>(other)) != _edges.end();
}

bool firenoo::GraphVertex::addEdge(GraphVertex* other, const std::string& id, double weight) {
	if(!hasEdge(other, id)) {
		std::string cpy(id);
		_edges[other] = std::pair<std::string, double>(cpy, weight);
		return true;
	}
	return false;
}

bool firenoo::GraphVertex::removeEdge(GraphVertex* other, const std::string& id) {
	if(hasEdge(other, id)) {
		_edges.erase(other);
		return true;
	}
	return false;
}