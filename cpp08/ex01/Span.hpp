#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
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

    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;

    template <typename InputIterator>
    void addRange(InputIterator begin, InputIterator end)
    {
        std::vector<int> values(begin, end);
        if (values.size() > _N - _numbers.size())
            throw std::runtime_error("Adding range would exceed Span capacity");
        _numbers.insert(_numbers.end(), values.begin(), values.end());
    }

private:
    unsigned int _N;
    std::vector<int> _numbers;
};

#endif
