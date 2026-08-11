#pragma once

#include <algorithm>
#include <iterator>
#include <iostream>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T &container, int value);

#include "easyfind.tpp"