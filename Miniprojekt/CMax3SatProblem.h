#pragma once
#include "COptimizer.h"
#include "VariableNeighbours.h"
#include "VariableAssignments.h"
#include "Clause.h"

class CMax3SatProblem
{
public:
	std::unique_ptr<COptimizer> optimizer;
	std::vector<Clause> clauses;
	VariableAssignments assignments;
	VariableNeighbours neighbours;
	UInteger variablesAmount = -1;

public:
	CMax3SatProblem(UInteger containerSize);
	void load(const std::string& filename);
	void printClauses();
	void afterLoadInit();
	double compute(bool* array, size_t size) const;
	const std::unique_ptr<int[]>& getBestResult(UInteger& size) const;

	inline UInteger getVariablesAmount() const { return variablesAmount; }
	const std::vector<Clause>& getClauses() const { return clauses; }
	const VariableAssignments& getVariableAssignmenst() const { return assignments; }
	const VariableNeighbours& getVariableNeighbours() const { return neighbours; }	
};

