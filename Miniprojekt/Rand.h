#pragma once
#include "Constants.h"


class Rand
{
	static std::random_device rd;
	static std::mt19937 mt;
	static uint32_t xorState;
	static uint32_t nextXorshift32();
	
	Rand() = delete; // no objects

public:

	static void initRNG();
	static uint32_t getInt()
	{
#ifdef XORSHIFT_MODE
		return nextXorshift32();
#else
		return mt();
#endif
	};
	static bool getBool() { return static_cast<bool>(getInt() % 2); }

};