#pragma once
#include "Constants.h"

struct VariableAssignments // wskazuje klauzule do ktorych nalezy dana zmienna
{
	Map<Integer,Set<Integer>> clauses;
	VariableAssignments(Integer size) { clauses.reserve(size); }
	
	inline bool contains(Integer index, Integer clause) const{
		return clauses.at(index).find(clause) != clauses.at(index).end();
	}
	
	inline void insert(Integer clause, Integer variable) { clauses[clause].insert(variable); }
	
};

