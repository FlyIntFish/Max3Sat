#include "CMax3SatProblem.h"

CMax3SatProblem::CMax3SatProblem(Integer sizeOfContainers) : optimizer(sizeOfContainers)
{
}

void CMax3SatProblem::load(const std::string& filename)
{
	std::ifstream file(filename);
	callAssert(file.good());
	Integer val1;
	Integer val2;
	Integer val3;
	while(file.ignore(10, ' ').eof() == false)
	{
		file >> val1 >> val2 >> val3;
		file.ignore(10, ')');
		bool positive1 = val1 > 0 ? true : false;
		bool positive2 = val2 > 0 ? true : false;
		bool positive3 = val3 > 0 ? true : false;
		val1 = absolute(val1);
		val2 = absolute(val2);
		val3 = absolute(val3);
			
		optimizer.clauses.emplace_back( val1, positive1, val2,positive2, val3, positive3 );
		optimizer.neighbours.insert(val1, val2);
		optimizer.neighbours.insert(val1, val3);
		optimizer.neighbours.insert(val2, val1);
		optimizer.neighbours.insert(val2, val3);
		optimizer.neighbours.insert(val3, val1);
		optimizer.neighbours.insert(val3, val2);
	}
	optimizer.variablesAmount = optimizer.neighbours.neighbours.size();
	
	afterLoadInit();	// this may be not the best idea to call this function directly in load
}

void CMax3SatProblem::afterLoadInit()
{
	optimizer.populations.allocMemory(AMOUNT_OF_POPULATIONS, optimizer.variablesAmount);
}


double CMax3SatProblem::populationAccuracy(Population& population)
{
	Integer passed = 0;
	Integer failed = 0;
	for(auto & i : optimizer.clauses)
	{
		if (i.check(population[i.val[0]], population[i.val[1]], population[i.val[2]]))
			++passed;
		else
			++failed;
	}
	return static_cast<double>(passed) / (passed + failed);
}


void CMax3SatProblem::printClauses()
{
	for (const auto& i : optimizer.clauses)
		std::cout << i << "\n";
}





