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
    void draw(Color color = Color::Green) const override 
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
        Shape* ps;
        Shape* pr = new Rectangle;
        pr->draw(Color::Green);
        Shape* pc = new Circle;
        ps = pr;
        ps->draw();
        ps = pc;
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
- Virtual functions are *dynamically bound* (resolved at runtime),
  but *default parameter values are statically bound* (resolved at compile time).

- This mismatch causes inconsistent behavior:
      Shape* pr = new Rectangle;
      pr->draw();  // calls Rectangle::draw(Shape::Red)!
  → The function invoked is Rectangle::draw, but the default argument (Red)
    is taken from Shape, because pr’s *static type* is Shape*.

- Why? Efficiency. Default arguments are bound at compile time for speed;
  changing this would complicate runtime dispatch.

- Duplicating default parameter values in base and derived classes leads to
  maintenance hazards (must update every derived class when the default changes).

- Solution: Use the **NVI (Non-Virtual Interface)** idiom:
    • Base class provides a non-virtual `draw(color = Red)` that calls
      a private virtual `doDraw(color)`.
    • Derived classes override `doDraw` only — no default value duplication.
    • The base class alone controls the default parameter.

- Relation to Item 36: Just as you should never redefine a non-virtual function,
  you should never redefine a default parameter, because both lead to
  inconsistent and confusing behavior.

→ Rule: Never redefine an inherited default parameter value.
   Use the NVI idiom to centralize defaults safely.
===============================================================================
*/
