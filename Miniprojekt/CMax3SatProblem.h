#pragma once
#include "Optimizer.h"
#include "VariableNeighbours.h"
#include "VariableAssignments.h"
#include "Clause.h"
#include <fstream>

class CMax3SatProblem
{
	Optimizer* optimizer = nullptr;
	std::vector<Clause> clauses;
	VariableAssignments assignments;
	VariableNeighbours neighbours;
	size_t variablesAmount = -1;

	void afterLoadInit(); // allocates memory for populations using information loaded from file (about amount of variables)

public:
	CMax3SatProblem(Integer containerSize);
	~CMax3SatProblem();
	void load(const std::string& filename);
	void printClauses();
	size_t getVariablesAmount() const { return variablesAmount; }

	const std::vector<Clause>& getClauses() const { return clauses; }
	const VariableAssignments& getVariableAssignmenst() const { return assignments; }
	const VariableNeighbours& getVariableNeighbours() const { return neighbours; }
	
};

