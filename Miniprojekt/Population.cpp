#include "Population.h"

Population::~Population()
{
	if (variables)
		delete[] variables;
}

Population& Population::operator=(const Population& cref)
{
	size = cref.size;
	std::memcpy(variables, cref.variables, size);
	return *this;
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


