#include <iostream>
#include <vector>
#include "Span.hpp"

int main()
{
	try
	{
		Span sp(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;

		// Large test
		const unsigned int SIZE = 10000;
		Span big(SIZE);
		std::vector<int> vals;
		vals.reserve(SIZE);
		for (unsigned int i = 0; i < SIZE; ++i)
			vals.push_back(static_cast<int>(i * 2));
		big.addRange(vals.begin(), vals.end());
		std::cout << "big shortest: " << big.shortestSpan() << std::endl;
		std::cout << "big longest: " << big.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}

