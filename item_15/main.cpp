#include <iostream>
#include <string>
#include <stdexcept>

class Investment
{
public:
    virtual void printInfo() const = 0;
    virtual ~Investment(){std::cout<< "Investment destroyed\n";}
    void increment(){++daysHeld;}
    int getDaysHeld() const {return daysHeld;}
private:
    int daysHeld = 0;
};

int daysHeld(Investment* pInv)
{
    return pInv->getDaysHeld();
}

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
std::shared_ptr<Investment> createInvestment(const std::string& investimentId)
{
    if(investimentId == "stock") return std::make_shared<Stock>(Stock());
    if(investimentId == "bond") return std::make_shared<Bond>(Bond());
    throw std::invalid_argument("Unknown investment ID");
}

int main()
{
    std::shared_ptr<Investment> spInv(createInvestment("stock"));
    spInv->increment(); // smart pointers overload the pointer dereferencing operators (operator-> and operator*)
    std::cout << "Days held: " << daysHeld(spInv.get()) << "\n"; // spInv.get() returns a raw pointer to be passed 
                                                                 // to the daysHeld function (explicit conversion).
    (*spInv).increment(); // overload operator*
    std::cout << "Days held: " << daysHeld(spInv.get()) << "\n"; 

}