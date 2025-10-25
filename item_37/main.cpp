#include <iostream>

enum class Color {Red, Green, Blue};

inline std::string colorToString(Color color) {
    switch (color) {
        case Color::Red:   return "Red";
        case Color::Green: return "Green";
        case Color::Blue:  return "Blue";
        default:                return "Unknown";
    }
}

class Shape
{
public:
    virtual void draw(Color color = Color::Red) const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape
{
public:
    void draw(Color color = Color::Green) const override 
                                                         // bad: solution do not override, just keep without any default parameter, 
                                                         // it will take the parameter from the Base class. 
    {
        std::cout << "Drawing Rectangle in color: " << colorToString(color) << "\n";
    }
    ~Rectangle() = default;
};

class Circle : public Shape
{
public:
    void draw(Color color = Color::Blue) const override 
                                                         // bad: solution do not override, just keep without any default parameter, 
                                                         // it will take the parameter from the Base class. 
    {
        std::cout << "Drawing Circle in color: " << colorToString(color) << "\n";
    }
    ~Circle() = default;
};

// Fix with the NVI pattern

class ShapeNVI
{
public:
    void draw(Color color) const {doDraw(color);}
    void draw() const {doDraw(defaultColor());}
    virtual ~ShapeNVI() = default;
protected:
    virtual void doDraw(Color color) const = 0;
    virtual Color defaultColor() const {return Color::Red;} // virtual default provider
};

class RectangleNVI : public ShapeNVI
{
public:
    ~RectangleNVI() = default;
protected:
    void doDraw(Color color) const override 
    {
        std::cout << "Drawing Rectangle in color: " << colorToString(color) << "\n";
    }
    Color defaultColor() const override {return Color::Green;} // override default provider
};

class CircleNVI : public ShapeNVI
{
public:
    ~CircleNVI() = default;
protected:
    void doDraw(Color color) const override 
    {
        std::cout << "Drawing Circle in color: " << colorToString(color) << "\n";
    }
    Color defaultColor() const override {return Color::Blue;} // override default provider
};

int main()
{
    std::cout << "Problems overriding default parameters on virtual functions.\n";
    {
        Shape* ps; // Static type: Shape*, Dynamic Type: null
        Shape* pr = new Rectangle; // Static type: Shape*, Dynamic Type: Rectangle*
        pr->draw(Color::Green);
        Shape* pc = new Circle; // Static type: Shape*, Dynamic Type: Circle*
        Rectangle r;
        r.draw();
        ps = pr; // Now ps dynamic Type is Rectangle*
        ps->draw();
        ps = pc; // Now ps dynamic Type is Circle*
        ps->draw();
        delete pr;
        delete pc;
    }
    std::cout << "Using NVI pattern with virtual default provider.\n";
    {
        ShapeNVI* ps;
        ShapeNVI* pr = new RectangleNVI;
        ShapeNVI* pc = new CircleNVI;
        ps = pr;
        ps->draw();
        ps = pc;
        ps->draw();
        delete pr;
        delete pc;
    }
}



/*
===============================================================================
 Item 37: Never redefine an inherited default parameter value
===============================================================================
- **Static Type**: The type an object or pointer is declared as in source code.
  Example:
      Shape* ps = new Rectangle;
  → ps has static type Shape*.

- **Dynamic Type**: The type of the object actually referenced at runtime.
  In the above example:
      ps's dynamic type is Rectangle*.

- **Binding Rules**:
    • Virtual functions are **dynamically bound** — the call resolves
      to the function of the object's dynamic type.
    • Default parameter values are **statically bound** — the compiler
      substitutes them based on the static type of the expression.

- This mismatch causes confusion:
      Shape* ps = new Rectangle;
      ps->draw();   // calls Rectangle::draw(Color::Red)!
  Even though Rectangle redefines draw(Color::Green), the default
  argument (Color::Red) comes from Shape because ps’s *static type*
  is Shape*.

- **Correct Design Approaches**:
    1. Don't redefine default parameters in derived classes — omit them.
       Let the base class default apply.
    2. If you want a new default, add an overload:
           void draw() const { draw(Color::Green); }
       (safe and explicit)
    3. Or use the NVI (Non-Virtual Interface) pattern:
           - Base defines draw(Color = Red)
           - Derived overrides doDraw(Color)
           - Optional: virtual Color defaultColor() for dynamic defaults.

- Rule: Never redefine an inherited default argument.
   Default parameters = static binding; virtuals = dynamic binding.
   Mixing them breaks expected polymorphic behavior.
===============================================================================
*/

