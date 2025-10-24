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
    {
        std::cout << "Drawing Rectangle in color: " << colorToString(color) << "\n";
    }
    ~Rectangle() = default;
};

class Circle : public Shape
{
public:
    void draw(Color color = Color::Green) const override
    {
        std::cout << "Drawing Rectangle in color: " << colorToString(color) << "\n";
    }
    ~Circle() = default;
};

int main()
{
    Shape* ps;
    Shape* pr = new Rectangle;
    Shape* pc = new Circle;
    ps = pr;
    ps->draw();
    ps = pc;
    ps->draw();
    delete pr;
    delete pc;
}