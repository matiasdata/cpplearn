#include <iostream>
#include <stdexcept>
#include <numeric>

// Bad design

class BadRational
{
public:
    BadRational(int n, int d) : num{n}, den{d} {} // denominator can be 0, nonsense
    int num, den; // public data can be modified
};


class Rational
{
public:
    Rational(int n, int d = 1)
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

// Stream output
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.getnum()<< "/" << r.getden();
}

int main() {
    Rational r1(2,4);                     // auto-normalized -> 1/2
    std::cout << "r1 = " << r1 << "\n";
    Rational r2 = 3;                      // implicit int -> Rational(3/1)
    std::cout << "r2 = " << r2 << "\n";
    r1 += r2;               // natural operator syntax
    std::cout << "sum = " << r1 << "\n";
}