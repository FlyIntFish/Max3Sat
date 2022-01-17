#pragma once

#include "Population.h"
#include <map>
class CMax3SatProblem;

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

	CMax3SatProblem* problemData = nullptr;
	Generation populations;
	size_t amountOfPopulations = 0;		// basically size of generation 
	size_t amountOfVariables = 0;		// amount of clauses is population
	float mutationProbability = 0.f;	// todo: should I change it to non-zero default values?
	float crossingProbability = 0.f;

public:

	Optimizer(CMax3SatProblem * problem, Integer variablesInPopulationAmount, Integer amountOfPopulations = AMOUNT_OF_POPULATIONS);
	Optimizer(const Optimizer&) = delete;
	~Optimizer() = default;
	
	Optimizer& operator=(const Optimizer&) = delete;


	
};

