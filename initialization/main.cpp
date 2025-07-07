#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;


class Widget
{
public:
    Widget(){}
    Widget(int x_,int y_, int z_) : x{x_}, y{y_},z{z_} {}
    Widget(std::initializer_list<int> il)
    {
        std::cout << "Calling initializer_list constructor\n";
        auto it = il.begin();
        x = (it != il.end())? *it++ : 0;
        y = (it != il.end())? *it++ : 0;
        z = (it != il.end())? *it++ : 0;
    }
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
    Widget w2{1,2,3}; // will call the initializer list constructor if implemented!
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
    std::cout << "w4: ";
    w4.printWidget();
    std::cout << "Type of w4: " << type_id_with_cvr<decltype(w4)>().pretty_name() << "\n";
    Widget w5(1,2,3); // will call the second constructor.
    std::cout << "w5: ";
    w5.printWidget();
    // Widget w6(1,2); // error: no instance of constructor "Widget::Widget" matches the argument list
    Widget w6{1,2}; // works fine, not initialized variables will be zero.
    std::cout << "w6: ";
    w6.printWidget();
    Widget w7{1,2,3,4}; // caution: extra variables will be ignored.
    std::cout << "w7: ";
    w7.printWidget();
    
    std::vector<int> v1(10,20); // non-std::initializer_list ctor: creates a size 10 vector with value 20 in all positions.
    std::vector<int> v2{10,20}; // std::initializer_list ctor: creates a size 2 vector with values {10,20}.
    std::cout << "\nv1: ";
    for(auto& x : v1) std::cout << x << " ";
    std::cout << "\nv2: ";
    for(auto& x : v2) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}

/* std::initializer_list<T> is a lightweight wrapper over an array of const T*, designed for brace-enclosed initializer syntax.
- Enables brace-based initialization (e.g., Widget w{1, 2, 3};).
- Used when writing constructors or functions that accept a fixed list of values.
- Lightweight, immutable view over a sequence of constant elements.
- Avoids dynamic memory allocation (unlike std::vector).
- Offers cleaner syntax and better performance for small, read-only sequences.
*/
