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

		void swap(Generation& gen);
		void operator=(Generation&& rval);
		inline double getAccuracyOf(size_t index) const { return populations[index].first; }
		inline Population& operator[](size_t index) const { return *populations[index].second; }		// utility to hide ugly syntax

		void randomizeAll();
		void allocMemory(size_t amountOfPopulations, size_t amountOfVariables);					// amount of variables in each population
		void sort() const;
		void updateAccuracy(const std::vector<Clause>& clauses);

	};

	CMax3SatProblem* problemData = nullptr;
	Generation * generations = nullptr;
	size_t amountOfVariables = 0;								 // amount of clauses is population
	size_t amountOfGenerations = AMOUNT_OF_GENERATIONS;
	size_t amountOfPopulations = AMOUNT_OF_POPULATIONS;			 // basically size of generation 
	size_t bottomLimitOfParents = BOTTOM_PARENTS_LIMIT;			 // don't take to tournament parents with index lower than this
	size_t tournamentSize = DEFAULT_TOURNAMENT_SIZE;			 // how many competitors in tournament
	int mutationProbability = DEFAULT_MUTATION_PROBABILITY;
	int crossingProbability = DEFAULT_CROSSING_PROBABILITY;
	int amountOfGenesToMutate = DEFAULT_AMOUNT_OF_GENES_TO_MUTATE;
	Generation buffer;

	Population* tournment(Generation & generation);
	void cross(Generation & parentsGen, Population& child1, Population& child2);
	void createNewPopulation (Generation& generation);
	void mutatePopulation(Population & population);
	void mutateGeneration(Generation& generation);

public:

	Optimizer(CMax3SatProblem * problem);
	~Optimizer();
	Optimizer(const Optimizer&) = delete;
	Optimizer& operator=(const Optimizer&) = delete;

	inline void setAmountOfGenerations(size_t amount) { amountOfGenerations = amount; }
	inline void setAmountOfPopulations(size_t amount) { amountOfPopulations = amount; }
	inline void setAmountOfVariables(size_t amount) { amountOfVariables = amount; }
	inline void setTournamentSize(size_t size) { tournamentSize = size; }
	inline void setCrossingProbability(int percent) { crossingProbability = percent; }
	inline void setMutationProbability(int percent) { mutationProbability = percent; }

	void initialize();

	void runIteration();
	
	
};

