#include <iostream>
#include <string>

class HFSOld
{
public:
    HFSOld(std::string address_, double sqmeters_, double price_) : address{address_}, sqmeters{sqmeters_}, price{price_} {}
    void print()
    {
        std::cout << "Address: " << address << "\n";
        std::cout << "Squared meters: " << sqmeters << "\n";
        std::cout << "Price: " << price << "\n";
    }
private:
    std::string address;
    double sqmeters;
    double price;
    HFSOld(const HFSOld&); //privately declared, unimplemented copy constructor
    HFSOld& operator=(const HFSOld&); // privately declared, unimplemented copy assignment operator.
};
// you need to declare the function so that the compiler will not generate the copy constructor or copy assignment automatically.
// if you declare and define private functions these could still be called by member functions and friend functions.
// but if these are not defined, then when called this will generate a link error.


class HFSNew
{
public:
    HFSNew(std::string address_, double sqmeters_, double price_) : address{address_}, sqmeters{sqmeters_}, price{price_} {}
    HFSNew(const HFSNew&) = delete;
    HFSNew& operator=(const HFSNew&) = delete;
    ~HFSNew() = default;
    void print()
    {
        std::cout << "Address: " << address << "\n";
        std::cout << "Squared meters: " << sqmeters << "\n";
        std::cout << "Price: " << price << "\n";
    }
private:
    std::string address;
    double sqmeters;
    double price;
};
// Since C++11, one can explicitely delete functions and declare them private.
// This will generate compile time error that are clear and preferred. 
// Do not use the privately declared unimplemented trick.

class Uncopyable
{
public:
    Uncopyable() = default;
    ~Uncopyable() = default;
    Uncopyable(const Uncopyable&) = delete;
    Uncopyable& operator=(const Uncopyable&) = delete;
};

class Logger : public Uncopyable
{
public:
    Logger(const std::string& name_) : name{name_} {}
private:
    std::string name;
};

// One can use inheritance to automate the process of doing a class uncopyable, by publicly inheriting from the 
// class Uncopyable which has deleted its copy constructor and copy assignment operators.
// Declaring any constructor can prevent the implicit generation of the default constructor. 

// By explicitly defaulting the default constructor and destructor, you ensure it's still available even if other constructors were added later.
// For Uncopyable, it's mainly about expressing that a no-argument constructor is desired.
// default explicitely instructs the compiler to generate these.

int main()
{
    HFSOld house1("58, 416 Manchester Road", 52.0, 450000.0);
    HFSOld house2("2, Poulton Court, Victoria road", 40.0, 300000.0);
    house1.print();
    house2.print();
    // house2 = house1; // error: 'operator=' is a private member of 'HFSOld'
    // HFSOld house3(house1); // error: calling a private constructor of class 'HFSOld'

    HFSNew nhouse1("58, 416 Manchester Road", 52.0, 450000.0);
    HFSNew nhouse2("2, Poulton Court, Victoria road", 40.0, 300000.0);
    nhouse1.print();
    nhouse2.print();
    // nhouse2 = nhouse1; // error: overload resolution selected deleted operator '='
    // note: candidate function has been explicitly deleted
    // HFSNew nhouse3(nhouse1); // error: call to deleted constructor of 'HFSNew'
    // note: 'HFSNew' has been explicitly marked deleted

    Logger log1("Hello, world!");
    Logger log2("My name is Matias");
    // log2 = log1; // error: object of type 'Logger' cannot be assigned because its copy assignment operator is implicitly deleted
    // note: copy assignment operator of 'Logger' is implicitly deleted because base class 'Uncopyable' has a deleted copy assignment operator
    // note: 'operator=' has been explicitly marked deleted here
    // Uncopyable& operator=(const Uncopyable&) = delete;
    // Logger log3(log1); // error: call to implicitly-deleted copy constructor of 'Logger'
    // note: copy constructor of 'Logger' is implicitly deleted because base class 'Uncopyable' has a deleted copy constructor  
    //  note: 'Uncopyable' has been explicitly marked deleted here
    // Uncopyable(const Uncopyable&) = delete;
}