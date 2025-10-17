#include <iostream>
#include "templategc.h"
#include "strategyfungc.h"

int main()
{
    TemplateApproach::Warrior w(20);
    std::cout << "Health: " << w.healthValue() << "\n";

    StratFunApproach::GameCharacter gc1(StratFunApproach::loseHealthFast);
    StratFunApproach::GameCharacter gc2(StratFunApproach::loseHealthSlow);
    std::cout << "gc1 Health: " << gc1.healthValue() << "\n";
    std::cout << "gc2 Health: " << gc2.healthValue() << "\n";

}