#include <vector>
#include <exception>
#include <cassert>
#include <iostream>
#include "graphw.hpp"
#include "graphwb.hpp"
#include "presets.hpp"

namespace firenoo {

//Test Suite
namespace test {

void testSuite1();
void testSuite2();
void testAddVertex();
void testRemoveVertex();
void testAddEdge();
void testRemoveEdge();
/*
 * Test Suite 1 - basic functions
 * - add vertex
 * - remove vertex
 * - add edge
 * - delete edge
 * - clear
 */
void testSuite1() {
	testAddVertex();
	testRemoveVertex();
	testAddEdge();
	testRemoveEdge();
}

void testAddVertex() {
	GraphW<int> g;
	for(size_t i = 0; i < 100; ++i) {
		g.addVertex(static_cast<int>(i)); //test &
	}
	g.addVertex(101); //test &&
	assert(g.vertexCount() == 101);
	assert(g.edgeCount() == 0);
	for(size_t i = 0; i < 100; ++i) {
		assert(g.hasVertex(static_cast<int>(i)));
	}
	assert(g.hasVertex(101));
}

void testRemoveVertex() {
	GraphW<int> g;
	for(size_t i = 0; i < 50; ++i) {
		g.addVertex(static_cast<int>(i));
	}
	
	auto vert = g.removeVertex(5);
	assert(!g.hasVertex(5));
	delete vert;
	int x = 10;
	vert = g.removeVertex(x);
	assert(!g.hasVertex(x));
	delete vert;
	assert(g.vertexCount() == 48);
}

void testAddEdge() {
	GraphW<int> g;
	assert(!g.addEdge(0, 1, 1.0));

	g.addVertex(0);
	g.addVertex(1);

	const double WEIGHT = 1.0;
	double w;
	assert(g.addEdge(0, 1, WEIGHT));
	assert(!g.hasEdge(1, 0));
	int a = 0, b = 1;
	assert(g.hasEdge(0, 1));
	assert(g.hasEdge(a, 1));
	assert(g.hasEdge(0, b));
	assert(g.hasEdge(a, b));
	w = 0;
	assert(g.getEdge(0, 1, w));
	assert(w == WEIGHT);
	w = 0;
	assert(g.getEdge(a, 1, w));
	assert(w == WEIGHT);
	w = 0;
	assert(g.getEdge(0, b, w));
	assert(w == WEIGHT);
	w = 0;
	assert(g.getEdge(a, b, w));
	assert(w == WEIGHT);
}

void testRemoveEdge() {

}

// void testEdge(firenoo::GraphW<int>& g);




}

}
int main() {
	firenoo::test::testSuite1();

}