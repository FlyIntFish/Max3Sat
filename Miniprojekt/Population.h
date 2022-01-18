#pragma once
#include "Constants.h"
#include "Clause.h"
#include "Rand.h"

struct Population
{
	bool* variables = nullptr;
	size_t size;

	Population() = default;
	~Population();
	Population& operator=(const Population& cref);
	
	void allocMemory(size_t size);
	inline bool& operator[](size_t index) { return variables[index]; }
	void randomize();

	
};

