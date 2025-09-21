#include <iostream>
#include <memory>

class Point
{
public:
    Point(int x, int y) : x{x}, y{y} {}
    void setX(int newX) { x = newX; }
    void setY(int newY) { x = newY; }
    void print() const { std::cout << "(" << x << "," << y << ")\n"; }
private:
    int x, y;
};

struct RectData
{
    RectData(Point ul, Point lr) : ulhc{ul}, lrhc{lr} {}
    Point ulhc; // upper-left-hand corner
    Point lrhc; // lower-right-hand corner
};

class Rectangle
{
public:
    Rectangle(Point ul, Point lr) : pData{std::make_shared<RectData>(ul,lr)} {}
    Point& upperLeft() const {return pData->ulhc;} // Dangerous: allows modification through "const" object
    Point& lowerRight() const {return pData->lrhc;} // Dangerous: allows modification through "const" object
    // correct alternative, return by value (a Point) although more expensive to do so, or return a const Point& (reference to a const Point).
private:
    std::shared_ptr<RectData> pData;
};


int main() {
    Rectangle r(Point(0,0), Point(10,10));
    const Rectangle cr(Point(0,0), Point(10,10));
    cr.upperLeft().print();
    cr.upperLeft().setX(5); // modifies internal state of a const object!
    cr.upperLeft().print();

}
