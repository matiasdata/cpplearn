#include <iostream>

class Base
{

public:
    void mf(){std::cout << "Calling Base::mf()\n";}
};

class Derived : public Base
{
public:
    void mf(){std::cout << "Calling Derived::mf()\n";} // Never redefine an inherited non-virtual function. Compiles, but shouldn't be done!
                                                        // mf3() should either be virtual or shouldn't be redefined.
};

int main()
{
    Derived d;
    Base* pB = &d;
    Derived* pD = &d;
    std::cout << "pB->mf() returns: ";
    pB->mf();
    std::cout << "pD->mf() returns: ";
    pD->mf(); // behavior of mf depends on the pointer, because we broke the is-a relationship. This shouldn't happen, 
              // the behavior shouldn't depend on the pointer type, but only on the object pointed to.
}