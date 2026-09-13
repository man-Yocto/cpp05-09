#include "PmergeMe.hpp"
#include <cctype>
#include <climits>
#include <ctime>

static bool parseNumber(const char *text, int& number)
{
	if (*text == '\0')
		return false;
	number = 0;
	for (int i = 0; text[i] != '\0'; ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(text[i])))
			return false;
		int digit = text[i] - '0';
		if (number > (INT_MAX - digit) / 10)
			return false;
		number = number * 10 + digit;
	}
	if (number == 0)
		return false;
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
