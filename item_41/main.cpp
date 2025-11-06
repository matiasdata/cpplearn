

#include <iostream>
#include <string>

// Runtime polymorphism via virtual functions and explicit interface
class Widget {
public:
    Widget() {}
    virtual ~Widget() {}

    virtual std::size_t size() const { return 42; }
    virtual void normalize() { std::cout << "Normalizing Widget\n"; }
    void swap(Widget& other) { std::cout << "Swapping Widgets\n"; }
};

Widget someNastyWidget;

// Function using explicit interface and runtime polymorphism
void doProcessing(Widget& w) {
    if (w.size() > 10 && &w != &someNastyWidget) {
        Widget temp(w);
        temp.normalize();
        temp.swap(w);
    }
}

// Template using implicit interface and compile-time polymorphism
template<typename T>
void doProcessingTemplate(T& w) {
    if (w.size() > 10 && w != someNastyWidget) {
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}

// Example type supporting implicit interface required by doProcessingTemplate
class Gadget {
public:
    std::size_t size() const { return 15; }
    void normalize() { std::cout << "Normalizing Gadget\n"; }
    void swap(Gadget&) { std::cout << "Swapping Gadgets\n"; }
    bool operator!=(const Gadget&) const { return false; }
};

int main() {
    std::cout << "=== Runtime Polymorphism Example ===\n";
    Widget w;
    doProcessing(w);

    std::cout << "\n=== Compile-Time Polymorphism Example ===\n";
    Gadget g;
    doProcessingTemplate(g);

    return 0;
}


/*

Summary:
---------
C++ offers two major paradigms for code reuse and polymorphism:

1. Object-Oriented Programming (OOP):
   - Uses *explicit interfaces*: These are visible in the source code (e.g., public member functions).
   - Employs *runtime polymorphism*: Achieved through virtual functions. The function called is determined at runtime based on the *dynamic type* of the object.

   Example: A `Widget` class with virtual methods whose behavior depends on the derived type at runtime.

2. Generic Programming with Templates:
   - Relies on *implicit interfaces*: There’s no formal declaration of the required interface. Instead, it’s inferred from the operations performed on a template type.
   - Uses *compile-time polymorphism*: Through function overloading and template instantiation. The exact function to call is determined at compile time.

   Example: A function template processes any object `T` as long as `T` supports the expressions invoked in the template (like `t.size()` or `t.normalize()`), even if those aren’t part of an explicit interface.

Key Ideas:
----------
- Explicit interfaces define “what” a type must support, visible through member signatures.
- Implicit interfaces define “how” a type is used in a template, enforced by valid expressions.
- Runtime polymorphism lets objects choose behavior at runtime.
- Compile-time polymorphism generates code based on type-specific operations at compile time.

Takeaway:
---------
Both paradigms offer interfaces and polymorphism, but they work differently.
Understanding these distinctions is essential for writing robust and reusable C++ code.
*/