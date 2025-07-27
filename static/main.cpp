#include <iostream>

int globalVar = 17; // static 
// global objects are static variables, even without the static keyword.

namespace myConstants
{
    constexpr double PI = 3.14159265; // static
}
// object defined on a namespace scope is also static.

int& counter()
{
    static int count = 0; // static
    ++count;
    return count;
}
// static variables inside functions are local static variables.
// These are initialized when they are called, and are destructed at the end of the program.

class MyTalkingInt
{
public:
    MyTalkingInt(int x_) : x{x_} {std::cout << "Created MyTalkingInt!\n";}
    ~MyTalkingInt(){std::cout << "Destructed MyTalkingInt\n";}
    int& operator++()
    {
        ++x;
        return x;
    }
    int& get(){return x;}
private: 
    int x{0};
};

class MyClass
{
public:
    MyClass()
    {
        ++TotalCreated;
        std::cout << "Created MyClass!\n";
    };
    ~MyClass()
    {
        std::cout << "Deleted MyClass!\n";
    }
    inline static MyTalkingInt TotalCreated{0}; // static
};

// static data members inside classes are non-local static objects.
// They are created before main and destructed at the end of the program.
// Before C++17 you jad to define as follows:
/* 
class MyClass
{
public:
    MyClass()
    {
        ++TotalCreated;
        std::cout << "Created MyClass!\n";
    };
    ~MyClass()
    {
        std::cout << "Deleted MyClass!\n";
    }
    static MyTalkingInt TotalCreated; // static
};
MyTalkingInt MyClass::TotalCreated{0};
*/


int main()
{
    int tempInt = 42; // stack allocated, not static
    counter();
    std::cout << "globalVar: " << globalVar << "\n";
    std::cout << "myConstants::PI: " << myConstants::PI << "\n";
    std::cout << "tempInt: " << tempInt << "\n";
    std::cout << "counter():"  << counter() << "\n";
    MyClass firstInstance;
    MyClass secondInstance;
    std::cout << "Total created: " << MyClass::TotalCreated.get() << "\n";

}


/*

A static object is one that exists from the time it’s constructed until the
end of the program. 
Excluded:
    * Stack allocated objects.
    * Heap allocated objects.
Included:
    * global objects.
    * objects defined at namespace scope.
    * objects declared static inside classe.
    * objects declared static inside functions.
    * objects declared static at file scope.
Static objects inside functions are known as local static
objects (because they’re local to a function), and the other
kinds of static objects are known as non-local static objects. 
Static objects are destroyed when the program exits,
i.e., their destructors are called when main finishes executing.

*/
