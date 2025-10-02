#pragma once

#include <iostream>

class Date
{
public:
    Date(int d, int m, int y);
    int getDay() const {return day;}
    int getMonth() const {return month;}
    int getYear() const {return year;}

private:
    int day;
    int month;
    int year;
};

std::ostream& operator<<(std::ostream& os, const Date& d);