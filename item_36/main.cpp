#include <iostream>

class Base
{

public:
    void mf(){ std::cout << "Calling Base::mf()\n"; }
    virtual ~Base() { std::cout << "Base destructor\n"; } // should be virtual, otherwise ~Derived() is never called on Base pointers.
};

class Derived : public Base
{
public:
    void mf(){ std::cout << "Calling Derived::mf()\n"; } // Never redefine an inherited non-virtual function.
                                                        // mf() should either be virtual or shouldn't be redefined.
    ~Derived(){ std::cout << "Derived destructor\n"; } 
};

int main()
{
    {
        std::cout << "Running mf() behavior example\n";
        Base* pB = new Derived;
        Derived* pD = new Derived;
        std::cout << "pB->mf() returns: ";
        pB->mf(); // calls Base::mf()
        std::cout << "pD->mf() returns: ";
        pD->mf(); // calls Derived::mf() behavior of mf depends on the pointer, because we broke the is-a relationship. 
                // This shouldn't happen, the behavior shouldn't depend on the pointer type, but only on the object pointed to.
        delete pB;
        delete pD;
    }

    {
        std::cout << "Running destructor behavior example\n";
        Base* pB = new Derived;
        pB->mf();
        delete pB;
    }
}

/*
===============================================================================
 Item 36: Never redefine an inherited non-virtual function
===============================================================================
- Non-virtual functions are *statically bound* — calls depend on the *type of the pointer/reference*,
  not the actual object type. This can cause inconsistent behavior:
      B* pB = &d; pB->mf();  // calls B::mf
      D* pD = &d; pD->mf();  // calls D::mf

- Redefining a non-virtual function in a derived class breaks the is-a relationship:
    • If D must change mf’s behavior, mf should be virtual.
    • If mf must always behave like in B, then D should not redefine it.
    • If D truly requires a different implementation, perhaps D should not inherit from B.

- Invariant rule: non-virtual functions define *common behavior for all derived classes*.

- Violating this rule leads to confusion, inconsistent semantics, and broken substitutability.

- Special case: destructors in polymorphic base classes must be virtual.
    • If a derived object is deleted through a base pointer and the base destructor is non-virtual,
      only the Base part is destroyed — the Derived destructor never runs.
    • This causes resource leaks and undefined behavior.
    • Making the destructor virtual ensures correct destruction order:
          Derived::~Derived() → Base::~Base()

→ Rule: Never redefine (hide) an inherited non-virtual function.
   If you need different behavior, make it virtual.
===============================================================================
*/
