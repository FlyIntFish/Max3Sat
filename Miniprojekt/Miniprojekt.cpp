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

	
}
