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

// 1. Pass-by-reference (non-universal)
template<typename T>
void byRef(T& param) {
    std::cout << "byRef - T: " << type_name<T>();
    std::cout << ", param: " << type_name<decltype(param)>() << "\n";
}

template<typename T>
void byConstRef(const T& param) {
    std::cout << "byConstRef - T: " << type_name<T>();
    std::cout << ", param: " << type_name<decltype(param)>() << "\n";
}

template<typename T>
void byPtr(T* param) {
    std::cout << "byPtr - T: " << type_name<T>();
    std::cout << ", param: " << type_name<decltype(param)>() << "\n";
}

// 2. Universal Reference
template<typename T>
void universalRef(T&& param) {
    std::cout << "universalRef - T: " << type_name<T>();
    std::cout << ", param: " << type_name<decltype(param)>() << "\n";
}

// 3. Pass-by-value
template<typename T>
void byValue(T param) {
    std::cout << "byValue - T: " << type_name<T>();
    std::cout << ", param: " << type_name<decltype(param)>() << "\n";
}

void someFunc(int, double) {}

int main() {
    std::cout << "--- Case 1: ParamType is a Reference or Pointer, but not a Universal Reference ---\n";
    int x = 10;
    const int cx = x;
    const int& rx = cx;
    const int *px = &x; // px is a pointer to x as a const int
    const int* const cpx = &x; 

    byRef(x);   // T=int, param=int&
    byRef(cx);  // T=const int, param=const int&
    byRef(rx);  // T=const int, param=const int&

    byConstRef(x);   // T=int, param=const int&
    byConstRef(cx);  // T=int, param=const int&
    byConstRef(rx);  // T=int, param=const int&
   
    byPtr(&x); // T is int, param's type is int*
    byPtr(px); // T is const int, param's type is const int*

    std::cout << "\n--- Case 2: Universal Reference ---\n";
    universalRef(x);   // T=int&, param=int&
    universalRef(cx);  // T=const int&, param=const int&
    universalRef(rx);  // T=const int&, param=const int&
    universalRef(42);  // T=int, param=int&& (rvalue)

    std::cout << "\n--- Case 3: Pass-by-value ---\n";
    byValue(x);   // T=int, param=int
    byValue(cx);  // T=int, param=int
    byValue(rx);  // T=int, param=int
    byValue(px);  // T=const int*, param=const int* (notice that the pointer is copied, but data is not).
    byValue(cpx); // T=const int*, param=const int* (constness of the pointer is lost, but still points to a const int).

    std::cout << "\n--- Special case: Arrays ---\n";
    const char name[] = "Matias Data";
    byValue(name); // T=const char*, param=const char*
    byRef(name);   // T=const char[13], param=const char (&)[13]

    std::cout << "\n--- Special case: Function Pointers ---\n";
    byValue(someFunc); // T=void (*)(int, double), param=void (*)(int, double)
    byRef(someFunc);   // T=void (int, double), param=void (&)(int, double)

    return 0;
}

/* 
On a call like this:

template<typename T>
void f(ParamType param);
f(expr);

Case 1: ParamType is a reference (T&) or a pointer (T*).    
Then the following rules apply: 
    a) If expr’s type is a reference, ignore the reference part.
    b) Then pattern-match expr’s type against ParamType to determine T.

Case 2: ParamType is a universal reference (T&&). In a function template taking a
type parameter T, a universal reference’s declared type is T&&, behavior is different for lvalues and rvalues.
Then the following rules apply: 
    a) If expr is an lvalue, both T and ParamType are deduced to be lvalue references.
    b) If expr is an rvalue, the “normal” (i.e., Case 1) rules apply.

Case 3: ParamType is Neither a Pointer nor a Reference (T).
When ParamType is neither a pointer nor a reference, we’re dealing with pass-by-
value. That means that param will be a copy of whatever is passed in—a completely new
object. Then the following rules apply: 
    a) As before, if expr’s type is a reference, ignore the reference part.
    b) If, after ignoring expr’s reference-ness, expr is const, ignore that, too.
*/