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
        return x;  // returns int&
}

template<typename T>
auto getVal(T& x) {
        return x;  // returns int&
}


int main()
{
    int x = 10;
    decltype(x) a = x;      // a is int
    decltype((x)) b = x;    // b is int& (notice the parentheses)

    std::cout << "Type of x is: " << type_name<decltype(x)>() << "\n";
    std::cout << "Type of a is: " << type_name<decltype(a)>() << "\n";
    std::cout << "Type of b is: " << type_name<decltype(b)>() << "\n";
    decltype(auto) y = add(a,b);
    std::cout << "Type of y=add(a,b) is: " << type_name<decltype(y)>() << "\n";
    std::cout << "Type of getRef(x) is: " << type_name<decltype(getRef(x))>() << "\n";
    std::cout << "Type of getVal(x) is: " << type_name<decltype(getVal(x))>() << "\n";
}