#include <iostream>
#include "templategc.h"

int main()
{
    TemplateApproach::Warrior w(20);
    std::cout << "Health: " << w.healthValue() << "\n";
}