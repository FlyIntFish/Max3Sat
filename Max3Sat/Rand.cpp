#include "Rand.h"
std::random_device Rand::rd;
uint32_t Rand::xorState;
std::mt19937 Rand::mt;

void Rand::initRNG()
{
	Rand::mt.seed(rd());
	Rand::xorState = rd();
}

uint32_t Rand::nextXorshift32()
{
	uint32_t x = xorState;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return xorState = x;
}


