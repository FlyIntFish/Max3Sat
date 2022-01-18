#include "Constants.h"
#include "CMax3SatProblem.h"
#include "Windows.h"
#include <chrono>
#include "Rand.h"

int main()
{
	Rand::initRNG();
	CMax3SatProblem problem(DEFAULT_CONTAINER_SIZE);
	problem.load("m3s_150_0.txt");
	problem.afterLoadInit();
	for(int i = 0; i < 20000; i++)
	{
		problem.optimizer->runIteration();
	}
	int size = 0;
	int * ptr = problem.getBestResult(size);
	bool* ptrbool = new bool[size];
	for(int i = 0; i < size; i++)
	{
		ptrbool[i] = bool(ptr[i]);
	}
	std::cout << problem.compute(ptrbool, size);

	delete[] ptrbool;
	
}
