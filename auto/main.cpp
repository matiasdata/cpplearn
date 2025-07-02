#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

struct Widget {
    int value;
    bool operator<(const Widget& other) const {
        return value < other.value;
    }
};

int main()
{
    // int x; // uninitialized, bad!
    // auto x; // error, must be initialized.
    auto x = 10; // ok, type is int
    std::cout << "Type of x: " << type_id_with_cvr<decltype(x)>().pretty_name() << "\n";
}