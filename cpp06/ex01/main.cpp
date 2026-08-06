#include "Serializer.hpp"
#include <iostream>

int main(void)
{
    Data data;
    data.value = 42;
    data.letter = 'Z';

    uintptr_t raw = Serializer::serialize(&data);
    Data* restored = Serializer::deserialize(raw);

    if (restored == &data)
    {
        std::cout << "Serialization works" << std::endl;
        std::cout << restored->value << std::endl;
        std::cout << restored->letter << std::endl;
    }
    else
    {
        std::cout << "Serialization failed" << std::endl;
        return 1;
    }
    return 0;
}
