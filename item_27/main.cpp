#include <iostream>

struct Base1 { int a; };
struct Base2 { int b; };

struct Derived : Base1, Base2 {
    int c;
};


class Window {
public:
    virtual void onResize(int size_) {
        std::cout << "Window::onResize called\n";
        size = size_;
    }
    void printSize(){std::cout << "Size: " << size << "\n";}
private:
    int size{0};
};

class SpecialWindow : public Window {
public:
    void onResize(int size_) override {
        
        //static_cast<Window>(*this).onResize(size_); // Wrong: creates a temporary Window object, does nothing to the current object!
        Window::onResize(size_); // correct approach, calls the base class onResize();
        std::cout << "SpecialWindow::onResize called\n";
    }
};

class Animal
{
public:
    virtual ~Animal() = default;
};

class Cow : public Animal
{
public:
    void makeSound(){std::cout << "Muuu" <<"\n";}
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

    Animal* pa = new Cow(); // create a pointer to a base1 object
    if(Cow* pc = dynamic_cast<Cow*>(pa)) // dynamic_cast to downcast a Animal* to Cow*. Only for polymorphic classes (with at least one virtual function).
    {
        pc->makeSound();
    }
    else
    {
        std::cout << "Not a Cow\n";
    }

    SpecialWindow sw;
    sw.onResize(10); // Wrong resize!
    sw.printSize();
    return 0;
}

/*

On most compilers you’ll see:
    * Derived* and Base1* are the same.
    * Base2* is offset (because Base2 lives after Base1 inside Derived).

This shows why a cast isn’t “free” — converting Derived* → Base2* requires adding an offset at runtime.

dynamic_cast
    Purpose: Safe downcasting in class hierarchies with virtual functions.
    Works only with polymorphic types (at least one virtual function).
    Checks at runtime if a base pointer/reference actually refers to a derived object.

Key facts:
    * If the cast is valid, you get a usable pointer.
    * If it’s invalid, you get nullptr (for pointers) or an exception (std::bad_cast) for references.
    * Cost: It’s usually implemented via runtime type information (RTTI). This can be slow in performance-critical code (string comparisons, vtable lookups, etc.).

Key Takeaways:
    * Avoid casts whenever practical, especially dynamic_casts in perfor-
    mance-sensitive code. If a design requires casting, try to develop a
    cast-free alternative.
    * When casting is necessary, try to hide it inside a function. Clients
    can then call the function instead of putting casts in their own code.
    * Prefer C++-style casts to old-style casts. They are easier to see, and
    they are more specific about what they do.
    * Pointer conversions may generate runtime code (offset adjustments).
    * Casts on *this can silently create temporaries, leading to incorrect behavior.

*/