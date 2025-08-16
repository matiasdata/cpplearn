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

class SharedFile
{
public:
    explicit SharedFile(const std::string& name) : filePtr{std::make_shared<std::string>(name)} {}
    void print() const 
    {
        std::cout << "Shared file: " << *filePtr << " (owners: " << filePtr.use_count() << ")\n";
    }
    // suppose we need to work with some API that receives pointers to strings.
    std::string* get() const // explicit conversion to an std::string*
    {
        return filePtr.get(); 
    }
    operator std::string*() const {return filePtr.get();} // implicit conversion to an std::string*
private:
    std::shared_ptr<std::string> filePtr;

};

// Function simulating an API that requires raw std::string*
void capitalize(std::string* str)
{
    std::transform(str->begin(), str->end(), str->begin(),
                   [](unsigned char c){return std::toupper(c);});
}

void underscore(std::string* str)
{
    std::transform(str->begin(), str->end(), str->begin(),
                   [](unsigned char c){return std::tolower(c);});
}

int main()
{
    std::shared_ptr<Investment> spInv(createInvestment("stock"));
    spInv->increment(); // smart pointers overload the pointer dereferencing operators (operator-> and operator*)
    std::cout << "Days held: " << daysHeld(spInv.get()) << "\n"; // spInv.get() returns a raw pointer to be passed 
                                                                 // to the daysHeld function (explicit conversion).
    (*spInv).increment(); // overload operator*
    std::cout << "Days held: " << daysHeld(spInv.get()) << "\n"; 

    SharedFile theFile("report.txt");
    theFile.print();

    capitalize(theFile.get()); // explicit conversion called 
    theFile.print();

    underscore(theFile); // implicit conversion called
    theFile.print();

}