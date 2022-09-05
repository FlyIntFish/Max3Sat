#include "COptimizer.h"
#include "CMax3SatProblem.h"

COptimizer::COptimizer(CMax3SatProblem* problem) : problemData(problem)
{
	amountOfVariables = problem->getVariablesAmount();
	bottomLimitOfParents = amountOfPopulations;
}

void COptimizer::Generation::randomizeAll()
{
	for (int i = 0; i < amountOfPopulations; i++)
		populations[i].second->randomize();
}

void COptimizer::initialize()
{
	if (generations)
		generations.reset();
	
	generations = std::make_unique<Generation[]>(amountOfGenerations);
	for (int i = 0; i < amountOfGenerations; i++)
	{
		generations[i].allocMemory(amountOfPopulations, amountOfVariables);
		generations[i].randomizeAll();
	}
	buffer.allocMemory(amountOfPopulations, amountOfVariables);
	bestSolution = std::make_unique<int[]>(amountOfVariables);
	for (int i = 0; i < amountOfGenerations; i++)
	{
		updateAccuracy();
		generations[i].sort();
	}
}


void COptimizer::Generation::operator=(Generation&& rval)
{
	amountOfPopulations = rval.amountOfPopulations;
	populations = std::move(rval.populations);
	rval.populations = nullptr;
	rval.amountOfPopulations = 0;
}

void COptimizer::Generation::swap(Generation& gen)
{
	auto tempPopulations = populations.release();
	size_t tempAmount = amountOfPopulations;

	populations = std::move(gen.populations);
	amountOfPopulations = gen.amountOfPopulations;

	gen.amountOfPopulations = tempAmount;
	gen.populations.reset(tempPopulations);
}

void COptimizer::Generation::allocMemory(size_t amountOfPopulations, size_t amountOfVariables)
{
	populations = std::make_unique< std::pair<double, std::unique_ptr<Population>>[] >(amountOfPopulations);
	for (int i = 0; i < amountOfPopulations; i++)
	{
		populations[i] = std::make_pair(0.0, std::make_unique<Population>());
		populations[i].second->allocMemory(amountOfVariables);
	}
}

void COptimizer::Generation::sort() const
{
	std::sort(populations.get(), populations.get() + amountOfPopulations, [](
		const std::pair<double, std::unique_ptr<Population>>& arg1,
		const std::pair<double, std::unique_ptr<Population>>& arg2
		)
		{return arg1.first > arg2.first; }
	);
}

void COptimizer::updateAccuracy()
{
	for (int i = 0; i < amountOfGenerations; i++)
	{
		for (int j = 0; j < amountOfPopulations; j++)
		{
			generations[i].populations[j].first = problemData->compute(
				generations[i].populations[j].second->variables.get(),
				generations[i].populations[j].second->size
			);
		}
	}
}

Population* COptimizer::tournment(Generation & generation)
{
	auto index = Rand::getUInt() % (bottomLimitOfParents);
	auto bestParentIndex = index;
	
	for(int i = 0; i < tournamentSize - 1; i++)
	{
		index = Rand::getUInt() % (bottomLimitOfParents );
		if (generation.getAccuracyOf(index) > generation.getAccuracyOf(bestParentIndex))
			bestParentIndex = index;
	}
	return &generation[bestParentIndex];
}

void COptimizer::createNewPopulation(Generation& gen)
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

void COptimizer::cross(Generation& parentsGen, Population& child1, Population& child2)
{
	Population* parent1 = tournment(parentsGen);
	Population* parent2 = tournment(parentsGen);

	UInteger crossingChance = Rand::getUInt() % 100;
	
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

void COptimizer::mutatePopulation(Population& population)
{
	for(int i = 0; i < amountOfGenesToMutate; i++)
	{
		auto index = Rand::getUInt() % population.size;
		population[index] = !population[index];
	}
}

void COptimizer::mutateGeneration(Generation& generation)
{
	for (int i = 0; i < generation.amountOfPopulations; i++)
	{
		if (Rand::getUInt() % 100 < mutationProbability)
			mutatePopulation(generation[i]);
	}
}

void COptimizer::migratePopulation(int sourceGenerationIndex)
{	
	auto destinationGenerationIndex = 0;
	do {
		destinationGenerationIndex = Rand::getUInt() % amountOfGenerations;
	} while (destinationGenerationIndex == sourceGenerationIndex);

	generations[destinationGenerationIndex][amountOfPopulations - 1] = generations[sourceGenerationIndex][0];
}

const std::unique_ptr<int[]>& COptimizer::getBestResult(UInteger& size) const
{
	size = amountOfVariables;
	return bestSolution;
}

void COptimizer::updateBestResult()
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

void COptimizer::runIteration()
{
	for (int i = 0; i < amountOfGenerations; i++)
	{
		if (Rand::getUInt() % 100 < migrationProbability)
			migratePopulation(i);

		createNewPopulation(generations[i]);

		if (Rand::getUInt() % 100 < mutationProbability)
			mutateGeneration(generations[i]);

		updateAccuracy();
		generations[i].sort();
		updateBestResult();
	}
}

