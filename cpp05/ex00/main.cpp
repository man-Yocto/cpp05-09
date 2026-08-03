#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat tooHigh("Alice", 0);
        (void)tooHigh;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    try
    {
        Bureaucrat tooLow("Bob", 151);
        (void)tooLow;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    try
    {
        Bureaucrat valid("Charlie", 75);
        std::cout << valid << std::endl;
        valid.incrementGrade();
        std::cout << valid << std::endl;
        valid.decrementGrade();
        std::cout << valid << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}