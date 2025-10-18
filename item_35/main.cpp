#include <iostream>
#include "virtual.h"
#include "templategc.h"
#include "strategyfungc.h"
#include "strategyclassicgc.h"
#include <memory>

int main()
{
    // Virtual approach
    VirtualApproach::GameCharacter vg(80);
    VirtualApproach::Warrior vw(50);
    std::cout << "GameCharacter vg Health: " << vg.healthValue() << "\n";
    std::cout << "Warrior vw Health: " << vw.healthValue() << "\n";

    //Template approach with Non Virtual Interface (NVI)
    TemplateApproach::GameCharacter g(50);
    TemplateApproach::Warrior w(20);
    std::cout << "GameCharacter g Health: " << g.healthValue() << "\n";
    std::cout << "Warrior w Health: " << w.healthValue() << "\n";


    // Functional Strategy approach
    StratFunApproach::GameCharacter gc1{StratFunApproach::loseHealthFast};
    StratFunApproach::GameCharacter gc2{StratFunApproach::loseHealthSlow()};
    StratFunApproach::GameCharacter gc3{StratFunApproach::loseHealthSuperSlow};
    std::cout << "gc1 Health: " << gc1.healthValue() << "\n";
    std::cout << "gc2 Health: " << gc2.healthValue() << "\n";
    std::cout << "gc2 Health: " << gc3.healthValue() << "\n";

    // Classic Strategy approach
    ClassicStrategyApproach::GameCharacter csgc1(std::make_shared<ClassicStrategyApproach::HealthCalculator>());
    ClassicStrategyApproach::GameCharacter csgc2(std::make_shared<ClassicStrategyApproach::FastDecay>());
    ClassicStrategyApproach::GameCharacter csgc3(std::make_shared<ClassicStrategyApproach::SlowDecay>());
    std::cout << "csgc1 Health: " << csgc1.healthValue() << "\n";
    std::cout << "csgc2 Health: " << csgc2.healthValue() << "\n";
    std::cout << "csgc2 Health: " << csgc3.healthValue() << "\n";
}

/*
On C++ most vexing parse:
In C++ anything that can be parsed as a declaration will be parsed as one. The following:
StratFunApproach::GameCharacter gc2(StratFunApproach::loseHealthSlow());
will be parsed as a function gc2 that returns a GameCharater and takes as input a function (that itself returns a loseHealthSlow object with no parameters).

int f(A()); 
is shorthand for:
int f(A(*)());
That is: f is a function taking a pointer to a function returning an A.
That’s a legacy rule going back to C. You can see the same behavior with 
int x(int());
which is a declaration of a function x that takes a pointer to a function returning int.
*/