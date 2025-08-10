#include <iostream>
#include <string>
#include <stdexcept>

class Investment
{
public:
    virtual void printInfo() const = 0;
    virtual ~Investment(){std::cout<< "Investment destroyed\n";}
};

class Stock : public Investment
{
public:
    virtual void printInfo() const override {std::cout << "Stock Investment\n";}
    virtual ~Stock(){std::cout << "Stock destroyed\n";}
};

class Bond : public Investment
{
public:
    virtual void printInfo() const override {std::cout << "Bond Investment\n";}
    virtual ~Bond(){std::cout << "Bond destroyed\n";}
};

// Simple factory function
Investment* createInvestment(const std::string& investimentId)
{
    if(investimentId == "stock") return new Stock();
    if(investimentId == "bond") return new Bond();
    throw std::invalid_argument("Unknown investment ID");
}


void rawptrExample()
{
    std::cout << "Calling Raw Pointer Example\n";
    try{
        Investment* pInv(createInvestment("stock")); // call factory function
        throw std::runtime_error("Something went wrong!"); // simulate exception
        delete pInv; // release object -> never called because an exception is thrown before
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }  
}

void uniqueptrExample()
{
    std::cout << "Calling Unique Pointer Example\n";
    try{
        std::unique_ptr<Investment> pInv(createInvestment("stock")); // call factory function
        throw std::runtime_error("Something went wrong!"); // simulate exception
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    // even when the exception is called, the unique pointer still calls its destructor automatically.  
}

void sharedptrExample()
{
    std::cout << "Calling Shared Pointer Example\n";
    try{
        std::shared_ptr<Investment> pInv(createInvestment("stock")); // call factory function
        throw std::runtime_error("Something went wrong!"); // simulate exception
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    // even when the exception is called, the unique pointer still calls its destructor automatically.  
}

int main()
{
    rawptrExample();
    uniqueptrExample();
    sharedptrExample();

    return 0;
}

/*
Summary:
Raw pointers don’t clean up automatically — exceptions or early returns cause leaks.
unique_ptr and shared_ptr use RAII (Resource Acquisition Is Initialization): their destructors run during stack unwinding,
ensuring resources are freed even if an exception is thrown. Resources are correctly released, regardless of how
control leaves a block.

===================== KEY POINTS =====================

1. Raw pointers require manual memory management.
   - If an exception or early return happens before 'delete', memory leaks occur.
   - High maintenance cost, easy to forget cleanup.

2. std::unique_ptr (single ownership):
   - Automatically deletes the resource when going out of scope.
   - Prevents leaks even with exceptions or early returns.
   - Cannot be copied (ownership is unique), but can be moved.

3. std::shared_ptr (shared ownership):
   - Reference counting ensures object is deleted only when the last shared_ptr goes out of scope.
   - Safer when multiple objects share the same resource.
   - Slightly more overhead due to reference counting.

4. Best Practice:
   - Use RAII: Acquire resource, wrap it immediately in a smart pointer.
   - Prefer std::unique_ptr by default; use std::shared_ptr only when shared ownership is required.
   - Avoid raw pointers for ownership unless absolutely necessary.

=======================================================


Key takeaways:
    * To prevent resource leaks, use RAII objects that acquire resources
    in their constructors and release them in their destructors.
    * Two commonly useful RAII classes are std::unique_ptr and std::shared_ptr.
*/