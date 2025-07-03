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

    // making code more portable.
    std::vector<int> v = {1, 2, 3, 4};
    auto sz = v.size(); // Better than unsigned or size_t (portable)
    std::cout << "Vector size: " << sz << "\n";
    std::cout << "Vector size type: " << type_id_with_cvr<decltype(sz)>().pretty_name() << "\n";

    // avoiding writing long/complex types automatically deduced by context.

    std::cout << "Iterating over a vector with auto:\n";
    for(auto it = v.begin(); it != v.end(); ++it)
    {
        auto val = *it;
        std::cout << "Value: " << val << "\n";
    }

    // compare with the following code.
    std::cout << "Iterating over a vector without auto:\n";
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        std::vector<int>::iterator::value_type val = *it;
        std::cout << "Value: " << val << "\n";
    }

    std::cout << "\n----- Closures -----\n";
    // Auto
    auto doubler = [](int n) { return n * 2; };
    std::cout << "Auto closure: " << doubler(10) << "\n";
    std::cout << "Type of doubler: " << type_id_with_cvr<decltype(doubler)>().pretty_name() << "\n";

    // Without Auto
    std::function<int(int)> doubler2 = [](int n) { return n * 2; };
    std::cout << "Manual closure: " << doubler2(10) << "\n";
    std::cout << "Type of doubler2: " << type_id_with_cvr<decltype(doubler2)>().pretty_name() << "\n";

    auto w1 = std::make_unique<Widget>(Widget{10});
    auto w2 = std::make_unique<Widget>(Widget{20});

    auto derefLess = [](const auto& p1, const auto& p2) {return *p1 < *p2;};

    std::cout << "derefLess: " <<  std::boolalpha << derefLess(w1, w2) << "\n";
    std::cout << "Type of derefLess: " << type_id_with_cvr<decltype(derefLess)>().pretty_name() << "\n";

    auto derefUPLess = [](const std::unique_ptr<Widget>& p1, 
                        const std::unique_ptr<Widget>& p2) 
                        {return *p1 < *p2;};

    std::cout << "derefUPLess: " <<  std::boolalpha << derefUPLess(w1, w2) << "\n";
    std::cout << "Type of derefUPLess: " << type_id_with_cvr<decltype(derefUPLess)>().pretty_name() << "\n";

    std::function<bool(const std::unique_ptr<Widget>&,
                     const std::unique_ptr<Widget>&)> 
    derefUPLess2 = [](const std::unique_ptr<Widget>& p1,
                     const std::unique_ptr<Widget>& p2) 
                     {return *p1 < *p2;};

    std::cout << "derefUPLess2: " <<  std::boolalpha << derefUPLess2(w1, w2) << "\n";
    std::cout << "Type of derefUPLess2: " << type_id_with_cvr<decltype(derefUPLess2)>().pretty_name() << "\n";
    
    


}