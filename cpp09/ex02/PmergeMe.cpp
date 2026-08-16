#include "PmergeMe.hpp"

struct PairData
{
	int small;
	int big;
};

int PmergeMe::nbr_of_comps = 0;

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) { (void)other; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return *this;
}
PmergeMe::~PmergeMe() {}

bool PmergeMe::compare(int a, int b)
{
	++nbr_of_comps;
	return a < b;
}

std::vector<int> PmergeMe::computeJacobsthalSequence(int upperBound)
{
	std::vector<int> sequence;
	int previous = 1;
	int current = 1;

	if (upperBound <= 0)
		return sequence;
	sequence.push_back(1);
	while (current <= upperBound)
	{
		sequence.push_back(current);
		current = current + 2 * previous;
		previous = sequence[sequence.size() - 2];
	}
	return sequence;
}

int PmergeMe::binaryInsertVector(std::vector<int>& main, int value, int boundIndex)
{
	int low = 0;
	int high = boundIndex;
	int middle;

	while (low < high)
	{
		middle = low + (high - low) / 2;
		if (compare(main[middle], value))
			low = middle + 1;
		else
			high = middle;
	}
	main.insert(main.begin() + low, value);
	return low;
}

void PmergeMe::fordJohnsonVector(std::vector<int>& elements, int groupSize)
{
	std::vector<PairData> pairs;
	std::vector<PairData> sortedPairs;
	std::vector<int> bigNumbers;
	std::vector<int> main;
	std::vector<int> order;
	bool hasOdd = false;
	int odd = 0;
	size_t i;

	(void)groupSize;
	if (elements.size() <= 1)
		return;
	if (elements.size() % 2 != 0)
	{
		hasOdd = true;
		odd = elements[elements.size() - 1];
	}
	for (i = 0; i + 1 < elements.size(); i += 2)
	{
		PairData pair;
		if (compare(elements[i + 1], elements[i]))
		{
			pair.small = elements[i + 1];
			pair.big = elements[i];
		}
		else
		{
			pair.small = elements[i];
			pair.big = elements[i + 1];
		}
		pairs.push_back(pair);
		bigNumbers.push_back(pair.big);
	}
	if (bigNumbers.empty())
		return;
	fordJohnsonVector(bigNumbers, groupSize * 2);
	std::vector<int> usedPairs(pairs.size(), 0);
	for (i = 0; i < bigNumbers.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (!usedPairs[j] && pairs[j].big == bigNumbers[i])
			{
				sortedPairs.push_back(pairs[j]);
				usedPairs[j] = 1;
				break;
			}
		}
	}
	main.push_back(sortedPairs[0].small);
	for (i = 0; i < bigNumbers.size(); ++i)
		main.push_back(bigNumbers[i]);
	for (size_t pairIndex = 1; pairIndex < sortedPairs.size(); ++pairIndex)
	{
		int value = sortedPairs[pairIndex].small;
		int bound = 0;
		while (main[bound] != sortedPairs[pairIndex].big)
			++bound;
		binaryInsertVector(main, value, bound);
	}
	if (hasOdd)
		binaryInsertVector(main, odd, static_cast<int>(main.size()));
	elements = main;
}

void PmergeMe::sortWithVector(std::vector<int>& input)
{
	fordJohnsonVector(input, 1);
}

std::list<int>::iterator PmergeMe::binaryInsertList(std::list<int>& main,
	int value, std::list<int>::iterator boundIt)
{
	std::list<int>::iterator it = main.begin();
	while (it != boundIt && compare(*it, value))
		++it;
	return main.insert(it, value);
}

void PmergeMe::fordJohnsonList(std::list<int>& elements, int groupSize)
{
	std::list<PairData> pairs;
	std::list<PairData> sortedPairs;
	std::list<int> bigNumbers;
	std::list<int> main;
	std::vector<int> order;
	bool hasOdd = false;
	int odd = 0;
	std::list<int>::iterator it;

	(void)groupSize;
	if (elements.size() <= 1)
		return;
	if (elements.size() % 2 != 0)
	{
		hasOdd = true;
		odd = elements.back();
	}
	it = elements.begin();
	while (it != elements.end())
	{
		int first = *it;
		++it;
		if (it == elements.end())
			break;
		int second = *it;
		++it;
		PairData pair;
		if (compare(second, first))
		{
			pair.small = second;
			pair.big = first;
		}
		else
		{
			pair.small = first;
			pair.big = second;
		}
		pairs.push_back(pair);
		bigNumbers.push_back(pair.big);
	}
	if (bigNumbers.empty())
		return;
	fordJohnsonList(bigNumbers, groupSize * 2);
	std::vector<int> usedPairs(pairs.size(), 0);
	size_t pairIndex = 0;
	for (std::list<int>::iterator bigIt = bigNumbers.begin(); bigIt != bigNumbers.end(); ++bigIt)
	{
		for (std::list<PairData>::iterator pairIt = pairs.begin(); pairIt != pairs.end(); ++pairIt, ++pairIndex)
		{
			if (!usedPairs[pairIndex] && pairIt->big == *bigIt)
			{
				sortedPairs.push_back(*pairIt);
				usedPairs[pairIndex] = 1;
				break;
			}
		}
		pairIndex = 0;
	}
	std::list<PairData>::iterator firstPair = sortedPairs.begin();
	main.push_back(firstPair->small);
	for (std::list<int>::iterator bigIt = bigNumbers.begin(); bigIt != bigNumbers.end(); ++bigIt)
		main.push_back(*bigIt);
	std::vector<PairData> pairVector(sortedPairs.begin(), sortedPairs.end());
	for (int index = static_cast<int>(pairVector.size()) - 1; index > 0; --index)
	{
		int value = pairVector[index].small;
		std::list<int>::iterator bound = main.begin();
		while (bound != main.end() && *bound != pairVector[index].big)
			++bound;
		binaryInsertList(main, value, bound);
	}
	if (hasOdd)
		binaryInsertList(main, odd, main.end());
	elements = main;
}

void PmergeMe::sortWithList(std::list<int>& input)
{
	fordJohnsonList(input, 1);
}

