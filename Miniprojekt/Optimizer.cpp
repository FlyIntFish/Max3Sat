#include "Optimizer.h"
#include "CMax3SatProblem.h"

Optimizer::Optimizer(CMax3SatProblem* problem) : problemData(problem)
{
	amountOfVariables = problem->getVariablesAmount();
	bottomLimitOfParents = amountOfPopulations;
}

void Optimizer::Generation::randomizeAll()
{
	for (int i = 0; i < amountOfPopulations; i++)
		populations[i].second->randomize();
}

void Optimizer::initialize()
{
	if (generations)
		delete[] generations;
	
	generations = new Generation[amountOfGenerations];
	for (int i = 0; i < amountOfGenerations; i++)
	{
		generations[i].allocMemory(amountOfPopulations, amountOfVariables);
		generations[i].randomizeAll();
	}
	buffer.allocMemory(amountOfPopulations, amountOfVariables);
	bestSolution = new int[amountOfVariables];
	for (int i = 0; i < amountOfGenerations; i++)
	{
		updateAccuracy();
		generations[i].sort();
	}
}

Optimizer::~Optimizer()
{
	if (generations)
		delete[] generations;
	if (bestSolution)
		delete[] bestSolution;
}

Optimizer::Generation::~Generation()
{
	if (populations)
	{
		for (int i = 0; i < amountOfPopulations; i++)
			delete populations[i].second;
		delete[] populations;
	}
}

void Optimizer::Generation::operator=(Generation&& rval)
{
	if (populations)
		delete[] populations;
	amountOfPopulations = rval.amountOfPopulations;
	populations = rval.populations;
	rval.populations = nullptr;
	rval.amountOfPopulations = 0;
}

void Optimizer::Generation::swap(Generation& gen)
{
	auto tempPopulations = populations;
	size_t tempAmount = amountOfPopulations;

	populations = gen.populations;
	amountOfPopulations = gen.amountOfPopulations;

	gen.amountOfPopulations = tempAmount;
	gen.populations = tempPopulations;
}

void Optimizer::Generation::allocMemory(size_t amountOfPopulations, size_t amountOfVariables)
{
	populations = new std::pair<double, Population*>[amountOfPopulations];
	for (int i = 0; i < amountOfPopulations; i++)
	{
		populations[i] = std::make_pair(0.0, new Population);
		populations[i].second->allocMemory(amountOfVariables);
	}
}

void Optimizer::Generation::sort() const
{
	std::sort(populations, populations + amountOfPopulations, [](
		const std::pair<double, Population*>& arg1,
		const std::pair<double, Population*>& arg2
		)
		{return arg1.first > arg2.first; });
}

void Optimizer::updateAccuracy()
{
	for(int i = 0; i < amountOfGenerations; i++)
		for (int j = 0; j < amountOfPopulations; j++)
			generations[i].populations[j].first = problemData->compute(
				generations[i].populations[j].second->variables,
					generations[i].populations[j].second->size);
}

Population* Optimizer::tournment(Generation & generation)
{
	auto index = Rand::getInt() % (bottomLimitOfParents);
	auto bestParentIndex = index;
	
	for(int i = 0; i < tournamentSize - 1; i++)
	{
		index = Rand::getInt() % (bottomLimitOfParents );
		if (generation.getAccuracyOf(index) > generation.getAccuracyOf(bestParentIndex))
			bestParentIndex = index;
	}
	return &generation[bestParentIndex];
}

void Optimizer::createNewPopulation(Generation& gen)
{
	for (int i = 0; i < elitismVariable; i++) 
	{
		buffer[i] = gen[i];
	}
	
	for(int i = elitismVariable; i < amountOfPopulations - 1; i+=2)
	{
		cross(gen, buffer[i], buffer[i + 1]);
	}
	gen.swap(buffer);
}

void Optimizer::cross(Generation& parentsGen, Population& child1, Population& child2)
{
	Population* parent1 = tournment(parentsGen);
	Population* parent2 = tournment(parentsGen);

	int crossingChance = Rand::getInt() % 100;
	
	if(crossingChance < crossingProbability)
	{
		for(int i = elitismVariable; i < amountOfVariables; i++)
		{
			if(Rand::getBool())
			{
				child1[i] = (*parent1)[i];
				child2[i] = (*parent2)[i];
			}
			else
			{
				child2[i] = (*parent1)[i];
				child1[i] = (*parent2)[i];
			}
		}
	}
	else
	{
		child1 = *parent1;
		child2 = *parent2;
	}
	
}

void Optimizer::mutatePopulation(Population& population)
{
	for(int i = 0; i < amountOfGenesToMutate; i++)
	{
		auto index = Rand::getInt() % population.size;
		population[index] = !population[index];
	}
}

void Optimizer::mutateGeneration(Generation& generation)
{
	for (int i = 0; i < generation.amountOfPopulations; i++)
		if (Rand::getInt() % 100 < mutationProbability)
			mutatePopulation(generation[i]);
}

void Optimizer::migratePopulation(int sourceGenerationIndex)
{	
	auto destinationGenerationIndex = 0;
	do {
		destinationGenerationIndex = Rand::getInt() % amountOfGenerations;
	} while (destinationGenerationIndex == sourceGenerationIndex);

	generations[destinationGenerationIndex][amountOfPopulations - 1] = generations[sourceGenerationIndex][0];
}

int* Optimizer::getBestResult(int& size)
{
	size = amountOfVariables;
	return bestSolution;
}

void Optimizer::updateBestResult()
{
	int gen = 0;
	for (int i = 1; i < amountOfGenerations; i++)
	{
		if (generations[gen].getAccuracyOf(0) < generations[i].getAccuracyOf(0))
			gen = i;
	}

	if (bestAccuracy < generations[gen].getAccuracyOf(0))
	{
		for (int i = 0; i < amountOfVariables; i++)
			bestSolution[i] = (int)generations[gen][0].variables[i];
		bestAccuracy = generations[gen].getAccuracyOf(0);
	}
}


void Optimizer::runIteration()
{
	for (int i = 0; i < amountOfGenerations; i++)
	{

		if (Rand::getInt() % 100 < migrationProbability)
			migratePopulation(i);
		
		createNewPopulation(generations[i]);

		if (Rand::getInt() % 100 < mutationProbability)
			mutateGeneration(generations[i]);

		updateAccuracy();
		generations[i].sort();

		updateBestResult();
		
	}
	// todo: for-loop for migration
}

