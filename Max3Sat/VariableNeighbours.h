#pragma once
#include <unordered_map>

#include "Constants.h"

struct VariableNeighbours	// wskazuje zmienne, ktore znajduja sie w jednej klauzuli z dana zmienna
{
	Map<Integer,Set<Integer>> neighbours;
	VariableNeighbours(Integer size) { neighbours.reserve(size); }

	inline bool contains(Integer variable, Integer neighbour) const {
		return neighbours.at(variable).find(neighbour) != neighbours.at(variable).end();
	}

	inline void insert(Integer variable, Integer neighbour) { neighbours[variable].insert(neighbour); }
	
};

