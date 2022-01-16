#pragma once

#include "VariableNeighbours.h"
#include "VariableAssignments.h"
#include "Population.h"
#include "Clause.h"

#include <map>

class Optimizer
{
	struct Generation
	{
		std::pair<double, Population*>* populations = nullptr;
		size_t amountOfPopulations = AMOUNT_OF_POPULATIONS;

		Generation() = default;
		~Generation();

		void operator=(Generation&& rval);
		inline double getAccuracyOf(size_t index) const { return populations[index].first; }
		inline Population& operator[](size_t index) const { return *populations[index].second; }		// utility to hide ugly syntax

		void allocMemory(size_t amountOfPopulations, size_t amountOfVariables);					// amount of variables in each population
		void sort() const;

	};

	Optimizer(Integer containerSize);
	~Optimizer() = default;
	
	Optimizer(const Optimizer&) = delete;
	Optimizer& operator=(const Optimizer&) = delete;

	VariableAssignments assignments;
	VariableNeighbours neighbours;
	std::vector<Clause> clauses;
	size_t variablesAmount = -1;
	Generation populations;

	friend class CMax3SatProblem;

public:


	
};

