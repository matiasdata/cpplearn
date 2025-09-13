#include <iostream>
#include <vector>


namespace WidgetStuff{

class WidgetImpl
{
public:
    WidgetImpl(const std::vector<double>& v_, const std::string& name_) : v{v_}, name{name_} {}
    void print() const {
        std::cout << "WidgetImpl data: ";
        for (auto& x : v) std::cout << x << " ";
        std::cout << "\n";
        std::cout << "Name: " << name << "\n";
    }
private:
    std::vector<double> v;
    std::string name;
    // possibly more data
};

class Widget
{
public:
    Widget(WidgetImpl* pImpl_) : pImpl{pImpl_} {}
    Widget(const std::vector<double>& v, const std::string& name) : pImpl{new WidgetImpl(v, name)} {}
    ~Widget(){delete pImpl;}
    Widget(const Widget& other) : pImpl{new WidgetImpl(*other.pImpl)} {}
    Widget& operator=(Widget other) // copy-and-swap (notice that parameter is not a const reference)
    {
        swap(other);
        return *this;
    }
    void print() const { pImpl->print(); }
    void swap(Widget& other) noexcept
    {
        using std::swap;
        swap(pImpl,other.pImpl); // simply swap pointers
    }
private:
    WidgetImpl* pImpl; // ptr to WidgetImpl
};

inline void swap(Widget& wa, Widget& wb) noexcept
{
    wa.swap(wb);
}

} // namespace WidgetStuff


// Specialization of std::swap must be in ::std, not inside WidgetStuff
namespace std
{
    using namespace WidgetStuff;
    template <>
    inline void swap<Widget>(Widget& wa,Widget& wb) // already noexcept as it calls noexcept member function, 
                                                    // but can't be declared noexcept as it is not in the standard library
    {
        wa.swap(wb);
    }
}

// Client code using swap
int main() {
    using namespace WidgetStuff;
    std::vector<double> v{1, 2};
    std::vector<double> w{3, 4, 5};
    Widget w1(v, "a");
    Widget w2(w,"b");


    std::cout << "Before swap:\n";
    w1.print();
    w2.print();

    using std::swap; // need to add this qualify and then call it without qualification.
    swap(w1, w2); // calls our efficient Widget::swap

    std::cout << "After swap:\n";
    w1.print();
    w2.print();
}

/*

Why three swap functions?
1. Member swap (Widget::swap): Provides the most efficient, noexcept way to swap 
   two Widgets by exchanging their internal pointers. This is the core implementation.
   Needed to have access to the private pointers, so that the non-member swap can call it.

2. Non-member swap (in WidgetStuff): Calls the member swap. Thanks to argument-
   dependent lookup (ADL), this version is found automatically when clients write
   `swap(a, b)` without qualification. This ensures the most efficient swap is used.

3. Specialization of std::swap: Some code (including parts of the standard library) 
   mistakenly qualifies swap as std::swap, bypassing ADL. By providing a total 
   specialization for Widget, we make sure even such code benefits from the efficient 
   swap implementation.

Together, these ensure Widget swapping is efficient, noexcept, and works correctly
in all contexts (unqualified calls with ADL, qualified std::swap calls, and generic 
code using templates).

Why "using std::swap;" before calling swap?

- We want to call the most efficient swap for the type T:
    * If T has its own overload of swap (found by ADL in T's namespace),
      we want to use that (e.g., WidgetStuff::swap).
    * Otherwise, we want to fall back on the generic std::swap.

- The `using std::swap;` line makes std::swap visible in the current scope.
  This ensures that when we later write `swap(a, b);` (unqualified call),
  the compiler considers BOTH:
      1. std::swap (now visible thanks to `using`), and
      2. any type-specific swap found by argument-dependent lookup (ADL).

- If a type-specific swap exists (like our WidgetStuff::swap), ADL ensures 
  it is chosen over std::swap, giving us the efficient, noexcept swap.
  If no type-specific swap exists, the call falls back to std::swap safely.

- If we skipped `using std::swap;` and wrote `swap(a, b);`, the compiler 
  would look only via ADL. If no type-specific swap is found, the call 
  would fail to compile (because std::swap wouldn’t be visible).

- If we instead wrote `std::swap(a, b);` directly, ADL is bypassed entirely, 
  and we’d always use std::swap — even when a more efficient type-specific 
  swap exists. This is exactly what we want to avoid.

Therefore, the correct pattern is:
    using std::swap;
    swap(a, b); // unqualified call, ADL + fallback

Key takeaways:
    * Provide a swap member function when std::swap would be inefficient
    for your type. Make sure your swap doesn’t throw exceptions.
    * If you offer a member swap, also offer a non-member swap that calls
    the member. For classes (not templates), specialize std::swap, too. For
    templates just offer a non-member function (not an specializatio or 
    overloading of std::swap).
    * When calling swap, employ a using declaration for std::swap, then call
    swap without namespace qualification.
    * It’s fine to totally specialize std templates for user-defined types, but
    never try to add something completely new to std.
*/