#pragma once
#include "Optimizer.h"
#include "VariableNeighbours.h"
#include "VariableAssignments.h"
#include "Clause.h"
#include <fstream>

class CMax3SatProblem
{public:
	Optimizer* optimizer = nullptr;
	std::vector<Clause> clauses;
	VariableAssignments assignments;
	VariableNeighbours neighbours;
	size_t variablesAmount = -1;


public:
	CMax3SatProblem(Integer containerSize);
	~CMax3SatProblem();
	void load(const std::string& filename);
	void printClauses();
	size_t getVariablesAmount() const { return variablesAmount; }
	void afterLoadInit();
	float compute(bool* array, size_t size) const;
	int* getBestResult(int& size) const;

	const std::vector<Clause>& getClauses() const { return clauses; }
	const VariableAssignments& getVariableAssignmenst() const { return assignments; }
	const VariableNeighbours& getVariableNeighbours() const { return neighbours; }
	
};

