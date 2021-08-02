#include <cassert>
#include "presets.hpp"


namespace firenoo {
	namespace directed {
		DirectedGraph<int> makePath(std::size_t length, double w) {
			assert(length > 0);
			DirectedGraph<int> result;
			for(std::size_t i = 0; i < length; ++i) {
				result.addVertex(i);
			}
			for(std::size_t i = 0; i < length - 1; ++i) {
				result.addEdge(i, i + 1, w);
			}
			return result;
		}

		DirectedGraph<int> make2WayPath(std::size_t length, double w) {
			assert(length > 0);
			DirectedGraph<int> result;
			for(std::size_t i = 0; i < length; ++i) {
				result.addVertex(i);
			}
			for(std::size_t i = 0; i < length - 1; ++i) {
				result.addEdge(i, i + 1, w);
				result.addEdge(i + 1, i, w);
			}
			return result;
		}


		DirectedGraph<int> makeCycle(std::size_t length, double w) {
			assert(length > 0);
			DirectedGraph<int> result = makePath(length, w);
			result.addEdge(length-1, 0, w);
			return result;
		}

		DirectedGraph<int> make2WayCycle(std::size_t length, double w) {
			assert(length > 0);
			DirectedGraph<int> result = make2WayPath(length, w);
			result.addEdge(length-1, 0, w);
			result.addEdge(0, length-1, w);
			return result;
		}

		DirectedGraph<int> makeComplete(std::size_t size, double w) {
			assert(size > 0);
			DirectedGraph<int> result;
			for(std::size_t i = 0; i < size; ++i) {
				result.addVertex(i);
			}
			for(std::size_t i = 0; i < size; ++i) {
				for(std::size_t j = i+1; j < size; ++j) {
					result.addBiEdge(i, j, w);
				}
			}
			return result;
		}

		DirectedGraph<int> makeChain(std::size_t length, double w) {
			assert(length > 0);
			DirectedGraph<int> result;
			for(std::size_t i = 0; i < length * 3 + 1; ++i) {
				result.addVertex(i);
			}
			for(unsigned int i = 0; i < length * 3; i += 3) {
				result.addEdge(i, i+1, w);
				result.addEdge(i, i+2, w);
				result.addEdge(i+1, i+3, w);
				result.addEdge(i+2, i+3, w);
			}
			return result;
		}

		DirectedGraph<int> make2WayChain(std::size_t length, double w) {
			assert(length > 0);
			DirectedGraph<int> result;
			for(std::size_t i = 0; i < length * 3 + 1; ++i) {
				result.addVertex(i);
			}
			for(unsigned int i = 0; i < length * 3; i += 3) {
				result.addEdge(i, i+1, w);
				result.addEdge(i, i+2, w);
				result.addEdge(i+1, i+3, w);
				result.addEdge(i+2, i+3, w);
				result.addEdge(i+1, i, w);
				result.addEdge(i+2, i, w);
				result.addEdge(i+3, i+1, w);
				result.addEdge(i+3, i+2, w);
			}
			return result;
		}
	}
}