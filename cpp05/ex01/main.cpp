#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    Bureaucrat boss("Boss", 1);
    Bureaucrat worker("Worker", 100);

    Form form1("Form1", 50, 25);
    Form form2("Form2", 150, 150);

    std::cout << boss << std::endl;
    std::cout << worker << std::endl;
    std::cout << form1 << std::endl;
    std::cout << form2 << std::endl;

    boss.signForm(form1);
    worker.signForm(form1);
    worker.signForm(form2);

    std::cout << form1 << std::endl;
    std::cout << form2 << std::endl;

    return 0;
}