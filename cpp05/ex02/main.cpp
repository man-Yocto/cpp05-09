#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    Bureaucrat highGrade("Alice", 1);
    Bureaucrat lowGrade("Charlie", 150);

    ShrubberyCreationForm shrub("home");
    RobotomyRequestForm robot("Bender");
    PresidentialPardonForm pardon("Fry");

    std::cout << "--- Signing tests ---" << std::endl;
    highGrade.signForm(shrub);
    lowGrade.signForm(robot);
    highGrade.signForm(robot);
    highGrade.signForm(pardon);

    std::cout << "\n--- Execute without signing ---" << std::endl;
    ShrubberyCreationForm unsigned_form("garden");
    highGrade.executeForm(unsigned_form);

    std::cout << "\n--- Execute signed, insufficient grade ---" << std::endl;
    lowGrade.signForm(shrub);
    lowGrade.executeForm(shrub);

    std::cout << "\n--- Execute signed, sufficient grade ---" << std::endl;
    highGrade.executeForm(shrub);
    highGrade.executeForm(robot);
    highGrade.executeForm(pardon);

    return 0;
}