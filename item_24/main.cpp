#include <iostream>
#include <numeric>
#include <stdexcept>

class Rational
{
public:
    Rational(int n = 0, int d = 1) // not explicit, so it can implicitely convert an integer into a rational
    {
        if (d==0) throw std::invalid_argument("Denominator can't be zero");
        Rational::simplify(n,d);
        num = n;
        den = d;
    }
    int getnum() const {return num;}
    int getden() const {return den;}
    Rational& operator+=(const Rational& other)
    {
        int pden = den*other.den;
        int pnum = num*other.den + other.num*den;
        Rational::simplify(pnum,pden);
        num = pnum;
        den = pden;
        return *this;
    }
private:
    int num, den;
    static inline void simplify(int& n, int& d)
    {
        int g = std::gcd(n,d);
        n = n/g;
        d = d/g;
        if (d < 0)
        {
            n = -n;
            d = -d; // have positive denominator
        }
    }
};

inline const Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.getnum() * rhs.getnum(), lhs.getden() * rhs.getden());
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.getnum()<< "/" << r.getden();
}


int main()
{
    Rational oneFourth(1, 4);
    Rational result;
    result = oneFourth * 2; 
    std::cout << "Result = " << result << "\n";
    result = 2 * oneFourth; 
    std::cout << "Result = " << result << "\n";
}