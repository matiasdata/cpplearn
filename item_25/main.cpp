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

    using std::swap;
    swap(w1, w2); // calls our efficient Widget::swap

    std::cout << "After swap:\n";
    w1.print();
    w2.print();
}