#include "Optimizer.h"

#include "CMax3SatProblem.h"

Optimizer::Optimizer(CMax3SatProblem* problem) : problemData(problem)
{
}

void Optimizer::Generation::randomizeAll()
{
	for (int i = 0; i < amountOfPopulations; i++)
		populations[i].second->randomize();
}

void Optimizer::initialize()
{
	generations = new Generation[amountOfGenerations];
	for (int i = 0; i < amountOfPopulations; i++)
	{
		generations[i].allocMemory(amountOfPopulations, amountOfVariables);
		generations[i].randomizeAll();
	}
	buffer.allocMemory(amountOfPopulations, amountOfVariables);
}

Optimizer::~Optimizer()
{

}

Optimizer::Generation::~Generation()
{
	if (populations)
	{
		for (int i = 0; i < amountOfPopulations; i++)
			delete populations[i].second;
	}
	delete[] populations;
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

void Optimizer::Generation::updateAccuracy(const std::vector<Clause>& clauses)
{
	for (int i = 0; i < amountOfPopulations; i++)
		populations[i].first = populations[i].second->accuracy(clauses);
}


Population* Optimizer::tournment(Generation & generation)
{
	auto index = Rand::getInt() % bottomLimitOfParents + 1;
	auto bestParentIndex = index;
	
	for(int i = 0; i < tournamentSize - 1; i++)
	{
		index = Rand::getInt() % bottomLimitOfParents + 1;
		if (generation.getAccuracyOf(index) > generation.getAccuracyOf(bestParentIndex))
			bestParentIndex = index;
	}
	return &generation[bestParentIndex];
}

void Optimizer::createNewPopulation(Generation& gen)
{
	for(int i = 0; i < amountOfPopulations - 1; i+=2)
	{
		cross(gen, buffer[i], buffer[i + 1]);
	}
	gen.swap(buffer);
}


void Optimizer::runIteration()
{
	for (int i = 0; i < amountOfGenerations; i++)
	{
		generations[i].updateAccuracy(problemData->getClauses());
		createNewPopulation(generations[i]);

		if( Rand::getInt() % 100 < mutationProbability)
			mutateGeneration(generations[i]);
	}
	// todo: for-loop for migration
}


void Optimizer::cross(Generation& parentsGen, Population& child1, Population& child2)
{
	Population* parent1 = tournment(parentsGen);
	Population* parent2 = tournment(parentsGen);

	int crossingChance = Rand::getInt() % 100;

	if(crossingProbability > crossingChance)
	{
		for(int i = 0; i < amountOfVariables; i++)
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

