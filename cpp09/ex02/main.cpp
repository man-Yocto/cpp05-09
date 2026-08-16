#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>
#include <ctime>

static bool parseNumber(const char *text, int& number)
{
	char *end;
	long value;
	if (*text == '\0')
		return false;
	value = std::strtol(text, &end, 10);
	if (*end != '\0' || value <= 0 || value > INT_MAX)
		return false;
	number = static_cast<int>(value);
	return true;
}

static void printNumbers(const char *label, const std::vector<int>& numbers)
{
	std::cout << label;
	for (size_t i = 0; i < numbers.size(); ++i)
		std::cout << (i == 0 ? "" : " ") << numbers[i];
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	std::vector<int> vectorInput;
	std::list<int> listInput;
	PmergeMe sorter;
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	for (int i = 1; i < argc; ++i)
	{
		int number;
		if (!parseNumber(argv[i], number))
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		vectorInput.push_back(number);
		listInput.push_back(number);
	}
	printNumbers("Before: ", vectorInput);
	std::clock_t vectorStart = std::clock();
	sorter.sortWithVector(vectorInput);
	double vectorTime = static_cast<double>(std::clock() - vectorStart) * 1000000.0 / CLOCKS_PER_SEC;
	std::clock_t listStart = std::clock();
	sorter.sortWithList(listInput);
	double listTime = static_cast<double>(std::clock() - listStart) * 1000000.0 / CLOCKS_PER_SEC;
	printNumbers("After: ", vectorInput);
	std::cout << "Time to process a range of " << vectorInput.size()
		<< " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << vectorInput.size()
		<< " elements with std::list : " << listTime << " us" << std::endl;
	return 0;
}
