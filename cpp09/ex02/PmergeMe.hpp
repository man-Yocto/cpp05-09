#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void	sortWithVector(std::vector<int>& input);
	void	sortWithList(std::list<int>& input);

	static int	nbr_of_comps;

private:
	void	fordJohnsonVector(std::vector<int>& elements, int groupSize);
	int		binaryInsertVector(std::vector<int>& main, int value, int boundIndex);

	void	fordJohnsonList(std::list<int>& elements, int groupSize);
	std::list<int>::iterator	binaryInsertList(std::list<int>& main,
				int value, std::list<int>::iterator boundIt);

	std::vector<int>	computeJacobsthalSequence(int upperBound);
	bool		compare(int a, int b);
};

#endif
