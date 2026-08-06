#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void)
{
    switch (std::rand() % 3)
    {
        case 0:
            return new A();
        case 1:
            return new B();
        default:
            return new C();
    }
}

void identify(Base* p)
{
    if (p == NULL)
    {
        std::cout << "Unknown" << std::endl;
        return;
    }
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}

void identify(Base& p)
{
    try
    {
        A& a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "A" << std::endl;
    }
    catch (...)
    {
        try
        {
            B& b = dynamic_cast<B&>(p);
            (void)b;
            std::cout << "B" << std::endl;
        }
        catch (...)
        {
            try
            {
                C& c = dynamic_cast<C&>(p);
                (void)c;
                std::cout << "C" << std::endl;
            }
            catch (...)
            {
                std::cout << "Unknown" << std::endl;
            }
        }
    }
}

int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    for (int i = 0; i < 10; ++i)
    {
        Base* ptr = generate();
        std::cout << "pointer: ";
        identify(ptr);
        std::cout << "reference: ";
        identify(*ptr);
        delete ptr;
    }
    return 0;
}
