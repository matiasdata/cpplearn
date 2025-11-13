#include <iostream>
#include <vector>  
#include <list>
#include <iterator>


template <typename T>
void print2nd(const T& container)
{
    if (container.size() >= 2)
    {
        typename T::const_iterator iter = container.begin();
        ++iter;
        std::cout << "Second element: " << *iter << "\n";
    }
}

/*
If we miss the typename the compiler will throw an error as it cannot parse this statement (it is ambiguous).
Alternatively, we can use auto in modern C++ (way easier and more readable, but need to understand auto type deduction).
 error: missing 'typename' prior to dependent type name 'T::const_iterator'
   12 |         T::const_iterator iter = container.begin();
      |         ^~~~~~~~~~~~~~~~~
      |         typename 
1 error generated.
*/

// exception to the rule: nested classes

template<typename T>
class Base {
public:
    class Nested {
    public:
        explicit Nested(int x) { std::cout << "Base::Nested(" << x << ")\n"; }
    };
};

template<typename T>
class Derived : public Base<T>::Nested // typename not allowed
{
public:
    explicit Derived(int x)
        : Base<T>::Nested(x)   // typename not allowed here in initialization
    {
        typename Base<T>::Nested temp(42); // typename needed here, two Base<T>::Nested object are created in this case
    }
};

int main()
{
    std::cout << "=== Use of typename for nested dependent typenames ===\n";
    std::vector<int> v{1,2,3};
    std::list<int> l{3,4,5};
    print2nd(v);
    print2nd(l);

    std::cout << "\n=== Typename rule exceptions ===\n";
    Derived<int> d(10);
}

/*

Summary:
    - When declaring template parameters, `class` and `typename` mean the same thing:
    template<class T>  → identical to → template<typename T>

    - BUT inside a template definition, when you refer to a **nested dependent type name**,
    you MUST precede it with `typename` to tell the compiler that it’s a type.

Example:
    typename C::const_iterator it = container.begin();

Otherwise, the compiler can’t know whether `C::const_iterator` is a type or a static member.

Rules:
    - Use `typename` for nested dependent *type* names (e.g., `typename C::iterator`).
    - Do NOT use `typename` in a base class list or initializer list:
    class Derived : public Base<T>::Nested { ... }  // typename not allowed here
    - It’s common to combine `typedef` with `typename`:
    typedef typename std::iterator_traits<IterT>::value_type value_type;

Key idea:
    - `typename` tells the compiler “this dependent name is a type,”
    preventing ambiguity during parsing.

==========================================================
*/
