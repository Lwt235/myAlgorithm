#pragma once
#ifndef _BASICGRAPH_
#define _BASICGRAPH_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

template <typename T>
class edge {
	int To;
	T weight;
	edge(int To, T weight) :To(To), weight(weight) {};
};

template<typename T>
void findDiameter(std::vector<std::vector<edge<T>>>& Graph, int u, int fa, std::vector<int>& rem, std::vector<int>& dp) {
	return;
}

#endif // !_BASICGRAPH_
