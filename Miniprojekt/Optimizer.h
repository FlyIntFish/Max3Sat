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

	};
public:	// todo: remove
	CMax3SatProblem* problemData = nullptr;
	Generation * generations = nullptr;
	size_t amountOfVariables = 0;								 // amount of clauses is population
	size_t amountOfGenerations = AMOUNT_OF_GENERATIONS;
	size_t amountOfPopulations = AMOUNT_OF_POPULATIONS;			 // basically size of generation 
	size_t bottomLimitOfParents = 0;							 // don't take to tournament parents with index lower than this, by default = amountOfVariables 
	size_t tournamentSize = DEFAULT_TOURNAMENT_SIZE;			 // how many competitors in tournament
	int mutationProbability = DEFAULT_MUTATION_PROBABILITY;
	int crossingProbability = DEFAULT_CROSSING_PROBABILITY;
	int migrationProbability = DEFAULT_MIGRATION_PROBABILITY;
	int amountOfGenesToMutate = DEFAULT_AMOUNT_OF_GENES_TO_MUTATE;
	int elitismVariable = DEFAULT_ELITISM_VARIABLE;
	Generation buffer;
	int* bestSolution = nullptr;
	float bestAccuracy = 0.f;
	
	Population* tournment(Generation & generation);
	void cross(Generation & parentsGen, Population& child1, Population& child2);
	void createNewPopulation (Generation& generation);
	void mutatePopulation(Population & population);
	void mutateGeneration(Generation& generation);
	void migratePopulation(int SourceGenerationIndex);
	void updateAccuracy();
	int* getBestResult(int& size);
	void updateBestResult();
	

public:
	void print()
	{
		for (int j = 0; j < amountOfGenerations; j++) {
			for (int i = 0; i < 20; i++)
				std::cout << i << ". " << generations[j].getAccuracyOf(i) << "\n";
			std::cout << "\n";
		}
	}
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
	inline void setMigrationProbability(int percent) { mutationProbability = percent; }
	inline void setElitismVariable(int amount) { elitismVariable = amount; }
	
	void initialize();

	void runIteration();
	
	
};

