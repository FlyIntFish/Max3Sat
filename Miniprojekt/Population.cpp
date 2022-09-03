#include "Population.h"

Population& Population::operator=(const Population& cref)
{
	size = cref.size;
	std::memcpy(variables.get(), cref.variables.get(), size);
	return *this;
}

void Population::allocMemory(size_t size_)
{
	size = size_;
	variables = std::make_unique<bool[]>(size_);
}

void Population::randomize()
{
	for(int i = 0; i < size; ++i)
	{
		variables[i] = Rand::getBool();
	}
}
