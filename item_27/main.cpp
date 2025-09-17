#include <iostream>

struct Base1 { int a; };
struct Base2 { int b; };

struct Derived : Base1, Base2 {
    int c;
};

int main() {
    Derived d;
    d.a = 10; d.b = 20; d.c = 30;

    Derived* pd = &d;
    Base1* pb1 = pd;  // may point at same address as pd
    Base2* pb2 = pd;  // will likely be at an offset!

    std::cout << "Address of Derived*: " << pd << "\n";
    std::cout << "Address as Base1*: " << pb1 << "\n";
    std::cout << "Address as Base2*: " << pb2 << "\n";

    return 0;
}

/*

On most compilers you’ll see:
    * Derived* and Base1* are the same.
    * Base2* is offset (because Base2 lives after Base1 inside Derived).

This shows why a cast isn’t “free” — converting Derived* → Base2* requires adding an offset at runtime.

*/