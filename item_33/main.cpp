#include <iostream>

class Base
{

public:
    Base(int x_) : x{x_} {}
    virtual void mf1() = 0;
    virtual void mf1(int y) {std::cout << "Calling Base::mf1(y) with y = "<< y <<"\n";}
    void mf3(){std::cout << "Calling Base::mf3()\n";}
    void mf3(int y){std::cout << "Calling Base::mf3(y) with y = "<< y <<"\n";}
    int getX(){return x;}
private:
    int x;
};

class Derived : public Base
{
public:
    using Base::mf1; //This makes all base-class overloads with this name visible in the derived class.
    using Base::mf3;
    Derived(int x_) : Base{x_} {}
    virtual void mf1() {std::cout << "Calling Derived::mf1()\n";} 
                                                                  
    void mf3(){std::cout << "Calling Derived::mf3()\n";} // Never redefine an inherited non-virtual function. Compiles, but shouldn't be done!
                                                        // mf3() should either be virtual or shouldn't be redefined.
};

int main()
{
    Derived thisDerived(10);
    thisDerived.mf1(); // Ok: calls Derived::mf1()
    thisDerived.mf1(5); // Error: Base::mf1(int) is hidden!
    // thisDerived.Base::mf1(5); // Ok: calls Base::mf1(int)
    thisDerived.mf3(); // Ok:  calls Derived::mf3()
    thisDerived.mf3(1); // Error: Base::mf3(double) is hidden!
    //thisDerived.Base::mf3(1); // Ok: calls Base::mf3(int)

    Base* pb = new Derived(10);
    pb->mf1(); // this will call Derived::mf1() because of polymorphism.
    pb->mf3(); // this will call Base::mf3() because Derived::mf3() is hiding Base::mf3(), but not overriding it.
}

/*
Key Takeaways:
    - In C++, derived class names hide all base class names with the same identifier.  
    - Use "using Base::func;" in Derived to make base overloads visible again.  
    - Prefer "using" for public inheritance (to preserve is-a behavior).  
    - Use "Base::func(...)" only for explicit one-off base calls or private inheritance.  
*/