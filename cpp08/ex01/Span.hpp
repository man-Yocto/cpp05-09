#pragma once

#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <limits>

class Span
{
public:
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int n);

    int shortestSpan() const;
    int longestSpan() const;

    template <typename InputIterator>
    void addRange(InputIterator begin, InputIterator end)
    {
        typename std::iterator_traits<InputIterator>::difference_type dist = std::distance(begin, end);
        if (dist <= 0)
            return;
        if (_numbers.size() + static_cast<size_t>(dist) > _N)
            throw std::runtime_error("Adding range would exceed Span capacity");
        for (InputIterator it = begin; it != end; ++it)
            _numbers.push_back(*it);
    }

private:
    unsigned int _N;
    std::vector<int> _numbers;
};
