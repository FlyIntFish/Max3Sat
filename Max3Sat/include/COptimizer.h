#pragma once

#include "Population.h"
#include <map>
class CMax3SatProblem;

class COptimizer
{
	struct Generation
	{
		std::unique_ptr< std::pair<double, std::unique_ptr<Population>>[] > populations;
		size_t amountOfPopulations = AMOUNT_OF_POPULATIONS;

		Generation() = default;

		void swap(Generation& gen);
		void operator=(Generation&& rval);
		inline double getAccuracyOf(size_t index) const { return populations[index].first; }
		inline Population& operator[](size_t index) const { return *populations[index].second; }

		void randomizeAll();
		void allocMemory(size_t amountOfPopulations, size_t amountOfVariables);		// amount of variables in each population
		void sort() const;

	};
	CMax3SatProblem* problemData = nullptr;
	Generation buffer;
	std::unique_ptr<int[]> bestSolution;
	std::unique_ptr<Generation[]> generations;
	UInteger amountOfVariables = 0;								 // amount of clauses is population
	UInteger amountOfGenerations = AMOUNT_OF_GENERATIONS;
	UInteger amountOfPopulations = AMOUNT_OF_POPULATIONS;		 // basically size of generation 
	UInteger bottomLimitOfParents = 0;							 // don't take to tournament parents with index lower than this, by default = amountOfVariables 
	UInteger tournamentSize = DEFAULT_TOURNAMENT_SIZE;			 // how many competitors in tournament
	UInteger mutationProbability = DEFAULT_MUTATION_PROBABILITY;
	UInteger crossingProbability = DEFAULT_CROSSING_PROBABILITY;
	UInteger migrationProbability = DEFAULT_MIGRATION_PROBABILITY;
	UInteger amountOfGenesToMutate = DEFAULT_AMOUNT_OF_GENES_TO_MUTATE;
	UInteger elitismVariable = DEFAULT_ELITISM_VARIABLE;
	double bestAccuracy = 0.0;
	
	Population* tournment(Generation & generation);
	void cross(Generation & parentsGen, Population& child1, Population& child2);
	void createNewPopulation (Generation& generation);
	void mutatePopulation(Population & population);
	void mutateGeneration(Generation& generation);
	void migratePopulation(int SourceGenerationIndex);
	void updateAccuracy();
	void updateBestResult();
	

public:
	const std::unique_ptr<int[]>& getBestResult(UInteger& size) const;
	COptimizer(CMax3SatProblem * problem);
	COptimizer(const COptimizer&) = delete;
	COptimizer& operator=(const COptimizer&) = delete;

	inline void setAmountOfGenerations(UInteger amount) { amountOfGenerations = amount; }
	inline void setAmountOfPopulations(UInteger amount) { amountOfPopulations = amount; }
	inline void setAmountOfVariables(UInteger amount) { amountOfVariables = amount; }
	inline void setTournamentSize(UInteger size) { tournamentSize = size; }
	inline void setCrossingProbability(UInteger percent) { crossingProbability = percent; }
	inline void setMutationProbability(UInteger percent) { mutationProbability = percent; }
	inline void setMigrationProbability(UInteger percent) { mutationProbability = percent; }
	inline void setElitismVariable(UInteger amount) { elitismVariable = amount; }
	
	void initialize();
	void runIteration();
};
