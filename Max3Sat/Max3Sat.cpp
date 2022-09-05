#include <string>
#include "Constants.h"
#include "CMax3SatProblem.h"
#include "Rand.h"

int main(int argc, char ** argv )
{
	if (argc < 3)
	{
		std::cout << "Run program with arguments: [path/to/file/filename.txt] [number_of_iterations]\n";
		return 1;
	}
	std::string filename(argv[1]);
	UInteger iterations = std::stoi(argv[2]);

	Rand::initRNG();
	CMax3SatProblem problem(DEFAULT_CONTAINER_SIZE);
	problem.load(filename);
	problem.afterLoadInit();

	for(int i = 0; i < iterations; i++)
	{
		problem.optimizer->runIteration();
	}

	UInteger size = 0;
	auto result = problem.getBestResult(size).get();
	std::unique_ptr<bool[]> values = std::make_unique<bool[]>(size);
	for(int i = 0; i < size; i++)
	{
		values[i] = static_cast<bool>(result[i]);
	}
	std::cout << problem.compute(values.get(), size) << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::printf("%-10d%s\n", i, (values[i] ? "1" : "0"));
	}
}
