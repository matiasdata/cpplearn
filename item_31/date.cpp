#include "date.h"

Date::Date(int d, int m, int y) : day{d}, month{m}, year{y} {}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << d.getDay() << "/" << d.getMonth() << "/" << d.getYear();
    return os;
}
