#include <iostream>
#include <cassert>

class Rectangle
{
public:
    Rectangle(double width_, double height_) : width{width_}, height{height_} {}
    virtual void setWidth(double newWidth){width = newWidth;}
    virtual void setHeight(double newHeight){height = newHeight;}
    virtual double getWidth(){return width;}
    virtual double getHeight(){return height;}
    virtual void print(){std::cout << "Rectangle of width " << getWidth() << " and height " << getHeight() << "\n";}

private:
    double width;
    double height;
};

class Square : public Rectangle
{
public:
    Square(double length) : Rectangle{length,length} {}
    void setWidth(double newWidth) override 
    {
        Rectangle::setWidth(newWidth);
        Rectangle::setHeight(newWidth);
    }
    void setHeight(double newHeight) override 
    {
        Rectangle::setWidth(newHeight);
        Rectangle::setHeight(newHeight);
    }
    void print() override {std::cout << "Square of length " << Rectangle::getWidth() << "\n";}
};

void Stretch(Rectangle & rect)
{
    double oldHeight = rect.getHeight();
    rect.setWidth(rect.getWidth()+10.0);
    assert(rect.getHeight() == oldHeight); // Always true for rectangles
}

int main()
{
    Rectangle r(20.0,10.0);
    r.print();
    Stretch(r);
    r.print();
    Square s(10.0);
    s.print();
    //Stretch(s); // error, assertion fails!
}

/* 

Item 32: Make sure public inheritance models "is-a".

Key: Takeaways:
    - Public inheritance means every derived class object *is-a* base class object.
    - Anything true for the base must also be true for the derived class.
    - Example: Student is-a Person, valid.  Penguin is-a Bird, invalid if Bird::fly() exists.
    - Incorrect hierarchies (e.g., Square is-a Rectangle) break behavioral consistency.
    - If an "is-a" relationship doesn’t hold in all cases, use composition ("has-a") or 
    implementation ("is-implemented-in-terms-of") instead of public inheritance.
    - Prefer designs that let compilers catch invalid uses at compile time.
*/