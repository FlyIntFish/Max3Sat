#pragma once
#include "Constants.h"
#include "Rand.h"

struct Population
{
	bool* variables = nullptr;
	size_t size;

	void allocMemory(size_t size);
	inline bool& operator[](size_t index) { return variables[index]; }
	void randomize();
	Population() = default;
	~Population();

	
};

