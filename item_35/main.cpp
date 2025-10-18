#include <iostream>
#include "templategc.h"
#include "strategyfungc.h"

int main()
{
    TemplateApproach::Warrior w(20);
    std::cout << "Health: " << w.healthValue() << "\n";

    StratFunApproach::GameCharacter gc1{StratFunApproach::loseHealthFast};
    StratFunApproach::GameCharacter gc2{StratFunApproach::loseHealthSlow()};
    // In C++ anything that can be parsed as a declaration will be parsed as one. The following:
    // StratFunApproach::GameCharacter gc2(StratFunApproach::loseHealthSlow());
    // will be parsed as a function gc2 that returns a GameCharater and takes as input a function (that itself returns a loseHealthSlow object with no parameters).
    StratFunApproach::GameCharacter gc3{StratFunApproach::loseHealthSuperSlow};
    std::cout << "gc1 Health: " << gc1.healthValue() << "\n";
    std::cout << "gc2 Health: " << gc2.healthValue() << "\n";
    std::cout << "gc2 Health: " << gc3.healthValue() << "\n";
}