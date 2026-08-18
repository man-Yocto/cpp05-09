#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
private:
    const std::string target;

public:
    RobotomyRequestForm();
    RobotomyRequestForm(const std::string &target);
    RobotomyRequestForm(const RobotomyRequestForm &other);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
    virtual ~RobotomyRequestForm();

    virtual void execute(const Bureaucrat &executor) const;
};

#endif