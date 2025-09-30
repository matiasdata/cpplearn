#pragma once

#include <iostream>

class Date
{
public:
    Date(int d, int m, int y);
    friend std::ostream& operator<<(std::ostream& os, const Date& d);

private:
    int day;
    int month;
    int year;
};