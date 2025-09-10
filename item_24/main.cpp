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
// Keep operator* as a non-member non-friend.
// The getter calls don’t hurt efficiency (they’ll inline). 
// Returning an int involves no heap allocation, no hidden copies — it’s literally just loading an integer from memory.
// This way, your Rational remains more encapsulated and extensible.

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

/*
Summary of Item 24:
If you need implicit type conversions on *all* parameters (not just the right-hand one),
the function must be a non-member. For example, operator*(Rational, Rational) should be
non-member so that both `oneHalf * 2` and `2 * oneHalf` compile correctly.
Being non-member does not mean it must be a friend — prefer using only the public interface
unless direct private access is truly necessary.
*/