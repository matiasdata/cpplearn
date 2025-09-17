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


int main() {
    Derived d;
    d.a = 10; d.b = 20; d.c = 30;

    Derived* pd = &d;
    Base1* pb1 = pd;  // may point at same address as pd
    Base2* pb2 = pd;  // will likely be at an offset!

    std::cout << "Address of Derived*: " << pd << "\n";
    std::cout << "Address as Base1*: " << pb1 << "\n";
    std::cout << "Address as Base2*: " << pb2 << "\n";


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