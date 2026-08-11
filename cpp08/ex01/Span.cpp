#include "Span.hpp"
#include <algorithm>

Span::Span(unsigned int n) : _N(n), _numbers()
{
}

Span::Span(const Span &other) : _N(other._N), _numbers(other._numbers)
{
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_N = other._N;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span()
{
}

void Span::addNumber(int n)
{
	if (_numbers.size() >= _N)
		throw std::runtime_error("Span is already full");
	_numbers.push_back(n);
}

int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers to find a span");
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	int minDiff = std::numeric_limits<int>::max();
	for (size_t i = 1; i < sorted.size(); ++i)
	{
		int diff = sorted[i] - sorted[i - 1];
		if (diff < minDiff)
			minDiff = diff;
	}
	return minDiff;
}

int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers to find a span");
	int minVal = *std::min_element(_numbers.begin(), _numbers.end());
	int maxVal = *std::max_element(_numbers.begin(), _numbers.end());
	return maxVal - minVal;
}

