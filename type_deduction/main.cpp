#include <iostream>
#include <string>

template <typename T>
std::string type_name() {
    std::string name = __PRETTY_FUNCTION__;
    auto start = name.find("T = ") + 4;
    auto end = name.find(']', start);
    return name.substr(start, (end - start));
}

// 1. Pass-by-reference (non-universal)
template<typename T>
void byRef(T& param) {
    std::cout << "byRef - T: " << type_name<T>() << "\n";
    std::cout << "byRef - param: " << type_name<decltype(param)>() << "\n";
}

template<typename T>
void byConstRef(const T& param) {
    std::cout << "byConstRef - T: " << type_name<T>() << "\n";
    std::cout << "byConstRef - param: " << type_name<decltype(param)>() << "\n";
}

template<typename T>
void byPtr(T* param) {
    std::cout << "byPtr - T: " << type_name<T>() << "\n";
    std::cout << "byPtr - param: " << type_name<decltype(param)>() << "\n";
}

// 2. Universal Reference
template<typename T>
void universalRef(T&& param) {
    std::cout << "universalRef - T: " << type_name<T>() << "\n";
    std::cout << "universalRef - param: " << type_name<decltype(param)>() << "\n";
}

// 3. Pass-by-value
template<typename T>
void byValue(T param) {
    std::cout << "byValue - T: " << type_name<T>() << "\n";
    std::cout << "byValue - param: " << type_name<decltype(param)>() << "\n";
}

// 4. Array deduction
template<typename T>
void arrayDecay(T param) {
    std::cout << "arrayDecay - T: " << type_name<T>() << "\n";
    std::cout << "arrayDecay - param: " << type_name<decltype(param)>() << "\n";
}

template<typename T>
void arrayRef(T& param) {
    std::cout << "arrayRef - T: " << type_name<T>() << "\n";
    std::cout << "arrayRef - param: " << type_name<decltype(param)>() << "\n";
}

// 5. Function pointer deduction
void someFunc(int, double) {}

template<typename T>
void funcDecay(T param) {
    std::cout << "funcDecay - T: " << type_name<T>() << "\n";
    std::cout << "funcDecay - param: " << type_name<decltype(param)>() << "\n";
}

template<typename T>
void funcRef(T& param) {
    std::cout << "funcRef - T: " << type_name<T>() << "\n";
    std::cout << "funcRef - param: " << type_name<decltype(param)>() << "\n";
}

int main() {
    std::cout << "--- Case 1: ParamType is a Reference or Pointer, but not a Universal Reference ---\n";
    int x = 10;
    const int cx = x;
    const int& rx = cx;
    byRef(x);   // T=int, param=const int&
    byRef(cx);  // T=int, param=const int&
    byRef(rx);  // T=int, param=const int&
    byConstRef(x);   // T=int, param=int&
    byConstRef(cx);  // T=const int, param=const int&
    byConstRef(rx);  // T=const int, param=const int&
    const int *px = &x;
    byPtr(&x); // T is int, param's type is int*
    byPtr(px); // T is const int, param's type is const int*

    std::cout << "\n--- Case 2: Universal Reference ---\n";
    universalRef(x);   // T=int&, param=int&
    universalRef(cx);  // T=const int&, param=const int&
    universalRef(rx);  // T=const int&, param=const int&
    universalRef(42);  // T=int, param=int&& (rvalue)

    std::cout << "\n--- Case 3: Pass-by-value ---\n";
    byValue(x);   // T=int, param=int
    byValue(cx);  // T=int, param=int (const discarded)
    byValue(rx);  // T=int, param=int

    std::cout << "\n--- Case 4: Arrays ---\n";
    const char name[] = "Matias Data";
    arrayDecay(name); // T=const char*, param=const char*
    arrayRef(name);   // T=const char[13], param=const char (&)[13]

    std::cout << "\n--- Case 5: Function Pointers ---\n";
    funcDecay(someFunc); // T=void (*)(int, double), param=void (*)(int, double)
    funcRef(someFunc);   // T=void (int, double), param=void (&)(int, double)

    return 0;
}
