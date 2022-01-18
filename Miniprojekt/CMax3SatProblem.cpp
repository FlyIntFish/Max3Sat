#include "CMax3SatProblem.h"

CMax3SatProblem::CMax3SatProblem(Integer containerSize = DEFAULT_CONTAINER_SIZE) : assignments(containerSize), neighbours(containerSize)
{
	clauses.reserve(containerSize);
}

CMax3SatProblem::~CMax3SatProblem()
{
	if (optimizer)
		delete optimizer;
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
			
		clauses.emplace_back( val1, positive1, val2,positive2, val3, positive3 );
		neighbours.insert(val1, val2);
		neighbours.insert(val1, val3);
		neighbours.insert(val2, val1);
		neighbours.insert(val2, val3);
		neighbours.insert(val3, val1);
		neighbours.insert(val3, val2);
	}
	variablesAmount = neighbours.neighbours.size();
}

void CMax3SatProblem::afterLoadInit()
{
	optimizer = new Optimizer(this);
	optimizer->initialize();
}

void CMax3SatProblem::printClauses()
{
	for (const auto& i : clauses)
		std::cout << i << "\n";
}

float CMax3SatProblem::compute(bool* array, size_t size) const
{
	Integer passed = 0;
	Integer failed = 0;
	for (const auto& i : clauses)
	{
		if (i.check(array[i.val[0]], array[i.val[1]], array[i.val[2]]))
			++passed;
		else
			++failed;
	}
	return static_cast<double>(passed) / (passed + failed);
}

int* CMax3SatProblem::getBestResult(int& size) const
{
	return optimizer->getBestResult(size);
}
