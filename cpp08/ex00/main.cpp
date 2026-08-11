#include <iostream>
#include <vector>
#include "easyfind.hpp"

int main()
{
	try
	{
		std::vector<int> v;
		for (int i = 1; i <= 5; ++i)
			v.push_back(i);

		std::vector<int>::iterator it = easyfind(v, 3);
		std::cout << "Found: " << *it << std::endl;

		// This should throw
		it = easyfind(v, 42);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}

