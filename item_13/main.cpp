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


Key takeaways:
    * To prevent resource leaks, use RAII objects that acquire resources
    in their constructors and release them in their destructors.
    * Two commonly useful RAII classes are std::unique_ptr and std::shared_ptr.
    std::shared_ptr is usually the better choice, because its behavior when
    copied is intuitive. Copying an std::unique_ptr sets it to null.
*/