#ifndef _FN_PROPERTIES
	#define _FN_PROPERTIES 0
	#include "graphw.hpp"
	
namespace firenoo {

	/*
	 * Checks whether the input graph is a directed, acyclic graph.
	 */
	template<class T, class W>
	bool is_dag(GraphW<T, W>& g);

}

#endif