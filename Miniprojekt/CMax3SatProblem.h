#pragma once
#include "Optimizer.h"

#include <fstream>

class CMax3SatProblem
{
	Optimizer optimizer;
	double populationAccuracy(Population & population);
	void afterLoadInit(); // allocates memory for populations using information loaded from file (about amount of variables)

public:
	CMax3SatProblem(Integer sizeOfContainers = DEFAULT_CONTAINER_SIZE);
	~CMax3SatProblem() = default;
	void load(const std::string& filename);
	void printClauses();

	
};

