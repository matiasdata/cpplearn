#include <iostream>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

class Widget
{
public:
    Widget(){}
    Widget(int x_,int y_, int z_) : x{x_}, y{y_},z{z_} {}
    int getx(){return x;}
    int gety(){return y;}
    int getz(){return z;}
    void setx(int nx){x = nx;}
    void sety(int ny){y = ny;}
    void setz(int nz){z = nz;}
    void printWidget()
    {
        std::cout << "x,y,z: " << x << "," << y << "," << z << "\n";
    }
private:
    int x{0}; // x's default value is zero.
    int y{0};
    int z{0};
};



int main()
{
    int x(0); // initializer is in parentheses
    int y = 0; // initializer follows "="
    int z{0}; // initializer is in braces
    int w = { 0 }; // rare: initializer uses "=" and braces

    std::cout << "x,y,z,w: " << x << "," << y << "," << z  << "," << w << "\n";

    int x2(1.0); // implicit casting
    int y2 = 1.0; // implicit casting
    // int z2{1.0}; // error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing] int z2{1.0}; 
    int z2{1};
    int sum{x2 + y2 + z2};
    std::cout << "sum: " << sum << "\n";

    Widget w1; // default constructor
    std::cout << "w1: ";
    w1.printWidget();
    Widget w2{1,2,3};
    std::cout << "w2: ";
    w2.printWidget();
    Widget w3(); // most vexing parse! declares a function named w2 that returns a Widget!
    /*
    main.cpp:45:14: warning: empty parentheses interpreted as a function declaration [-Wvexing-parse]
    Widget w2(); // most vexing parse! declares a function named w2 that returns a Widget!

    note: replace parentheses with an initializer to declare a variable
    Widget w2(); // most vexing parse! declares a function named w2 that returns a Widget!
    */
    std::cout << "Type of w3: " << type_id_with_cvr<decltype(w3)>().pretty_name() << "\n";

    Widget w4{};
    w4.printWidget();
    std::cout << "Type of w4: " << type_id_with_cvr<decltype(w4)>().pretty_name() << "\n";
    return 0;
}
