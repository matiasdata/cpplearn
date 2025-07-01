#include <iostream>
#include <string>

template <typename T>
std::string type_name() {
    std::string name = __PRETTY_FUNCTION__;
    auto start = name.find("T = ") + 4;
    auto end = name.find('\0', start);
    auto myFunType = name.substr(start, (end - start));
    myFunType.pop_back();
    return myFunType;
}

// Used with trailing return type syntax to express return types dependent on parameters.
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// When using auto, reference-ness is dropped. Use decltype(auto) to preserve the exact type.
template<typename T>
decltype(auto) getRef(T& x) {
        return x;  // returns int& (a reference, does not copy).
}

template<typename T>
auto getVal(T& x) {
        return x;  // returns int, makes a copy.
}

template<typename T>
auto& getRef2(T& x) {
        return x;  // returns int& (a reference, does not copy).
}

template <typename T>
class TD; // TD = "Type Displayer".
// if you try to instantiate an object of class TD it will return an error as the class is declared but undefined.
// The IDE will elicit an error message with the type of T.

int main()
{
    int x = 10;
    decltype(x) a = x;      // a is int
    decltype((x)) b = x;    // b is int& (notice the parentheses)
    const int * px = &x;
    const int& rx = x;

    std::cout << "Type of x is: " << type_name<decltype(x)>() << "\n";
    std::cout << "Type of a is: " << type_name<decltype(a)>() << "\n";
    std::cout << "Type of b is: " << type_name<decltype(b)>() << "\n";
    decltype(auto) y = add(a,b);
    std::cout << "Type of y=add(a,b) is: " << type_name<decltype(y)>() << "\n";
    std::cout << "Type of getRef(x) is: " << type_name<decltype(getRef(x))>() << "\n";
    std::cout << "Type of getVal(x) is: " << type_name<decltype(getVal(x))>() << "\n";
    std::cout << "Type of getRef2(x) is: " << type_name<decltype(getRef2(x))>() << "\n";
    std::cout << "Type of rx: " << typeid(rx).name() << "\n";
    std::cout << "Type of px: " << typeid(px).name() << "\n";
    // TD<decltype(b)> bType; // error: incomplete type "TD<int &>" is not allowed
}

/*
Common Uses of decltype:
- To get the exact type of an expression, including const/ref qualifiers.
- To deduce complex return types in function templates.
- To preserve reference-ness via decltype(auto) in return statements or declarations.
- Prefer decltype(auto) over auto when you want decltype-style type deduction.
- auto uses template type deduction rules, so if the returned value is a reference, the reference is usually stripped.
- Watch out for decltype((x)) vs decltype(x): the first gives a reference!
*/