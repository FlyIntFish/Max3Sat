#include "Optimizer.h"

Optimizer::Optimizer(Integer containerSize) : assignments(containerSize), neighbours(containerSize)
{
	clauses.reserve(containerSize);
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
	amountOfPopulations = rval.amountOfPopulations;
	for (int i = 0; i < amountOfPopulations; i++)
	{
		populations[i] = std::make_pair(rval.populations[i].first, rval.populations[i].second);
		rval.populations[i].second = nullptr;
	}
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