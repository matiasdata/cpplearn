#include <iostream>
#include <numeric>
#include <stdexcept>

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
    friend Rational operator*(const Rational& lhs, const Rational& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
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

// The below would be an error to return a reference to a Rational, as result is a local variable, it would be an ex-Rational.
// also would be wrong to allocate heap memory and return such rational, as that would create memory leaks.

// Rational& operator*(const Rational& lhs, const Rational& rhs){ // buggy code
//     Rational result(lhs.num * rhs.num, lhs.den * rhs.den);
//     return result;
// }


// The below is also wrong, because it has a memory leak, memory is allocated in the heap that can never be deleted as the
// user has no access to such pointers. At this point there’s no leak yet, because the object still exists in memory. 
// But you, as the caller, have no pointer, only a const Rational&. That means you cannot delete it.
// const Rational& operator*(const Rational& lhs, const Rational& rhs){ // buggy code
//     Rational* pres = new Rational(lhs.num * rhs.num, lhs.den * rhs.den);
//     return *pres;
// }

Rational operator*(const Rational& lhs, const Rational& rhs){
    Rational result(lhs.num * rhs.num, lhs.den * rhs.den);
    return result;
}


// Stream output
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.num<< "/" << r.den;
}

int main()
{
    Rational x(1,3);
    std::cout << "x is equal to " << x << "\n";
    Rational y(2,5);
    std::cout << "y is equal to " << y << "\n";
    Rational z = x * y;
    std::cout << "z = x * y is equal to " << z << "\n";
    Rational w = x * y * z; // same as operator*(operator*(x, y), z)
    std::cout << "w = x * y * z is equal to " << w << "\n"; 
}

/*
If I make the error of returning a reference to an ex-Rational (reference to a local variable):
const Rational& operator*(const Rational& lhs, const Rational& rhs){
    Rational result(lhs.num * rhs.num, lhs.den * rhs.den);
    return result;
}
the we get the following warning:
main.cpp:46:12: warning: reference to stack memory associated with local variable 'result' returned [-Wreturn-stack-address]
   46 |     return result;
      |            ^~~~~~
We are in undefined behavior, however the code compiles and returns the right answer, because memory has been deallocated 
but has not been changed (in this case, it could have been).
z = x * y is equal to 2/15


Correct implementation returns a value:
Rational operator*(const Rational& lhs, const Rational& rhs){
    Rational result(lhs.num * rhs.num, lhs.den * rhs.den);
    return result;
}


Even if callers are conscientious and well intentioned, there’s not
much they can do to prevent leaks in reasonable usage scenarios like
this:
Rational w, x, y, z;
w = x * y * z; // same as operator*(operator*(x, y), z)
Here, there are two calls to operator* in the same statement, hence two
uses of new that need to be undone with uses of delete. Yet there is no
reasonable way for clients of operator* to make those calls, because
there’s no reasonable way for them to get at the pointers hidden
behind the references being returned from the calls to operator*. This
is a guaranteed resource leak.
*/