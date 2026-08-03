#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    Intern someIntern;
    Bureaucrat boss("Boss", 1);

    std::cout << "--- Valid form names ---" << std::endl;
    AForm* f1 = someIntern.makeForm("shrubbery creation", "home");
    AForm* f2 = someIntern.makeForm("robotomy request", "Bender");
    AForm* f3 = someIntern.makeForm("presidential pardon", "Fry");

    std::cout << "\n--- Invalid form name ---" << std::endl;
    AForm* f4 = someIntern.makeForm("time travel request", "Nobody");

    std::cout << "\n--- Using the created forms ---" << std::endl;
    if (f1)
    {
        boss.signForm(*f1);
        boss.executeForm(*f1);
    }
    if (f2)
    {
        boss.signForm(*f2);
        boss.executeForm(*f2);
    }
    if (f3)
    {
        boss.signForm(*f3);
        boss.executeForm(*f3);
    }

    delete f1;
    delete f2;
    delete f3;
    delete f4;

    return 0;
}