
// main.cpp
#include <iostream>
#include "person.h"
#include "date.h"

int main() {
    Date birthday(9, 12, 1990);
    Person p("Alice", birthday);

    std::cout << p << std::endl;
    return 0;
}