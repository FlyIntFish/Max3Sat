#include "Constants.h"
#include "CMax3SatProblem.h"
#include "Windows.h"
#include <chrono>
#include "Rand.h"

void cross(Population & p1, Population& p2, Population & dest)
{
	for(int i = 0; i < p1.size; i++)
	{
		if (Rand::getBool())
			dest[i] = p1[i];
		else
			dest[i] = p2[i];
	}
}

void randomizeWorst(CMax3SatProblem::Generation & gen)
{
	for (int i = 20; i < gen.amountOfPopulations; i++)
		gen[i].randomize();
}

void mutate(Population & p, int mutationAmount = 30)
{
	for (int i = 0; i < mutationAmount; i++) 
	{
		size_t index = Rand::getInt() % p.size;
		p[index] = !p[index];
	}
}

void crossBestWithReplace(CMax3SatProblem::Generation & gen)
{
	int pivot = 20;
	CMax3SatProblem::Generation newGen;
	newGen.allocMemory(AMOUNT_OF_POPULATIONS, gen.populations[0].second->size);
	for (int i = 0; i < 10; i++)
		cross(gen[i], gen[i], newGen[i]);	// primitive copying
	for (int i = 10; i < AMOUNT_OF_POPULATIONS; i++)
	{
		cross(gen[Rand::getInt() % pivot], gen[Rand::getInt() % pivot], newGen[i]);
	}
	gen = std::move(newGen);
}

void crossBest(CMax3SatProblem::Generation & gen)
{
	int pivot = 50;
	for(int i = pivot; i < AMOUNT_OF_POPULATIONS; i++)
	{
		cross(gen[Rand::getInt() % pivot], gen[Rand::getInt() % pivot], gen[i]);
	}
}

void crossTournment(CMax3SatProblem::Generation& gen, int percent)
{
	int maxIndex = gen.amountOfPopulations / 100 * percent;
	CMax3SatProblem::Generation newGen;
	newGen.allocMemory(AMOUNT_OF_POPULATIONS, gen.populations[0].second->size);
	for (int i = 0; i < AMOUNT_OF_POPULATIONS; i++)
	{
		int temp = Rand::getInt() % maxIndex;
		int parent1Index = Rand::getInt() % maxIndex;
		if (parent1Index < temp)
			parent1Index = temp;
		temp = Rand::getInt() % maxIndex;
		int parent2Index = Rand::getInt() % maxIndex;
		if (parent2Index < temp)
			parent2Index = temp;
		cross(gen[parent1Index], gen[parent2Index], newGen[i]);
	}
	gen = std::move(newGen);
}

int main()
{
	Rand::initRNG();
	//system("color 2");	// essential instruction for every fancy program
	CMax3SatProblem problem;
	problem.load("m3s_150_0.txt");
	double acc = 0.0;
	for(int i = 0; i < AMOUNT_OF_POPULATIONS; i++)
	{
		problem.populations[i].randomize();
	}
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < AMOUNT_OF_POPULATIONS; i++)
	{
		problem.populations.populations[i].first = problem.populationAccuracy(problem.populations[i]);
	}

	problem.populations.sort();
	int counter = 0;
	constexpr int iterations = 10000;
	for (int j = 0; j < iterations; j++)
	{
		//randomizeWorst(problem.populations);
		crossTournment(problem.populations, 40);

		for (int i = 0; i < AMOUNT_OF_POPULATIONS; i++)
			if (Rand::getInt() % 100 <= 10 )
				mutate(problem.populations[i], 30);

		for (int i = 0; i < AMOUNT_OF_POPULATIONS; i++)
		{
			problem.populations.populations[i].first = problem.populationAccuracy(problem.populations[i]);
		}

		problem.populations.sort();
	}

	auto time = std::chrono::system_clock::now() - start;

	for (int i = AMOUNT_OF_POPULATIONS - 1; i >= 0; i--)
		std::cout << i << ".\t" << problem.populations.getAccuracyOf(i) << "\n";
	

	//for (int i = 0; i < 1000; i++)
	//	std::cout << Rand::getInt() % 100 << "\n";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count()<< "ms";
	//problem.printClauses();
}
