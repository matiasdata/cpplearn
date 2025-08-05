#include <iostream>

class MyInt
{
public:
    MyInt() : val{0} {}
    MyInt(const int& val_) : val{val_} {}
    MyInt& operator=(const MyInt& rhs) // return type is a reference to the current class
    {
        val = rhs.val;
        return *this; // return the left-hand object
    }
    MyInt& operator=(const int& rhs) // return type is a reference to the current class
    {
        val = rhs;
        return *this; // return the left-hand object
    }
    MyInt& operator+=(const int& rhs)
    {
        val += rhs;
        return *this;
    }
    MyInt& operator++() // prefix increment operator, no parameters.
    {
        ++val;
        return *this;
    }
    MyInt operator++(int) // postfix increment has a dummy int parameter to differentiate (used always, part of the language design).
    {
        MyInt temp = *this;
        ++(*this); // calls the pre-increment operator already defined, alternatively use ++val;
        return temp;
    }
    const int& get(){return val;}
private:
    int val;
};

int main()
{
    MyInt x{5};
    MyInt y{3};
    MyInt z;
    std::cout << "x: " << x.get() << "\ny: " << y.get() << "\nz: " << z.get() << "\n";
    x = y = z = 15; // equivalent to x = (y = (z = 15));
    std::cout << "x: " << x.get() << "\ny: " << y.get() << "\nz: " << z.get() << "\n";
    y = (++x);
    z++;
    std::cout << "x: " << x.get() << "\ny: " << y.get() << "\nz: " << z.get() << "\n"; 
}


/* 
Key Takeaways:
    * Have assignment operators return a reference to *this.
*/