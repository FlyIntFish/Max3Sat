#include "Population.h"

Population::~Population()
{
	if (variables)
		delete[] variables;
}

void Population::allocMemory(size_t size_)
{
	size = size_;
	variables = new bool[size_]{};
}

void Population::randomize()
{
	for(int i = 0; i < size; ++i)
	{
		variables[i] = Rand::getBool();
	}
}

double Population::accuracy(const std::vector<Clause>& clauses) const
{
	Integer passed = 0;
	Integer failed = 0;
	for (const auto& i : clauses)
	{
		if (i.check(variables[i.val[0]], variables[i.val[1]], variables[i.val[2]]))
			++passed;
		else
			++failed;
	}
	return static_cast<double>(passed) / (passed + failed);
}


