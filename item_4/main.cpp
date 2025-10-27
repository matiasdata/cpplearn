#include <iostream>
#include <string>
#include <list>

using PhoneNumber = unsigned long; //one could use a more appropriate implementation, this is just for illustrative purposes


// MyString is just a string wrapper that talks when constructors/assignment/destructors are called.
class MyString
{
public:
    MyString() : str{} 
    {
        std::cout << "Called MyString default constructor\n";
    }
    MyString(const std::string& str_) : str{str_} 
    {
        std::cout << "Called MyString constructor\n";
    }
    MyString(const MyString& other) : str{other.str} 
    {
        std::cout << "Called MyString Copy constructor\n";
    }
    MyString& operator=(const MyString& other)
    {
        str = other.str;
        std::cout << "Called MyString Copy assignment\n";
        return *this;
    }
    
    const std::string& get() const {return str;}
    
    std::string& get() 
    {
        return const_cast<std::string&>(static_cast<const MyString&>(*this).get());
    }

    ~MyString()
    {
        std::cout << "Called MyString destructor\n";
    }
private:
    std::string str;
};


class ABEntry // ABEntry = "Address Book Entry"
{
public:
    ABEntry(const std::string& name, 
        const std::string& address, 
        const std::list<PhoneNumber>& phones);
    void consult() 
    {
        std::cout << "Name: " << theName.get() << "\n";
        std::cout << "Address: " << theAddress.get() << "\n";
        std::cout << "Phone Numbers: ";
        for(auto it = thePhones.begin(); it != thePhones.end(); ++it)
        {
            std::cout << *it;
            if(std::next(it) != thePhones.end()) {std::cout <<", ";}
        }
        std::cout << "\n";
        ++numTimesConsulted;
    }

private:
    MyString theName;
    MyString theAddress;
    std::list<PhoneNumber> thePhones;
    int numTimesConsulted;
};

//inefficient, does not initialize variables thus default initializers are called and then they are copy assigned.
// ABEntry::ABEntry(const std::string& name, 
//     const std::string& address, 
//     const std::list<PhoneNumber>& phones)
// {
//     theName = name;
//     theAddress = address;
//     thePhones = phones;
//     numTimesConsulted = 0;
    
// }


// efficient version, all initialized

ABEntry::ABEntry(const std::string& name, 
                const std::string& address,
                const std::list<PhoneNumber>& phones) : 
                theName{name}, 
                theAddress{address}, 
                thePhones{phones},
                numTimesConsulted{0} {}



int main()
{
    ABEntry me("Matias","Collins Avenue 1540",{0111543524520});
    me.consult();

    ABEntry mom("Viviana","Callao 128",{543543554,54134515134});
    mom.consult();
    return 0;
}
/*
with the inefficient constructor
ABEntry me("Matias","Collins Avenue 1540",{0111543524520});
prints:
Called MyString default constructor         // the string theName is default constructed.
Called MyString default constructor         // the string.theAddress is default constructed.
Called MyString constructor                 // the string name is used to create a MyString by calling the ctor that takes a string.
Called MyString Copy assignment             // theName is copy assigned to this string.
Called MyString destructor                  // the auxiliary created MyString is destructed.
Called MyString constructor                 // the string name is used to create a MyString by calling the ctor that takes a string.
Called MyString Copy assignment             // theName is copy assigned to this string.
Called MyString destructor                  // the string name is used to create a MyString by calling the ctor that takes a string.


whit the efficient constructor
ABEntry me("Matias","Collins Avenue 1540",{0111543524520});
prints:
Called MyString constructor                 // the string theName is initialized with the ctor that takes a string.
Called MyString constructor                 // the string theAddress is initialized with the ctor that takes a string.


Things to Remember:

     * Manually initialize objects of built-in type, because C++ only
    sometimes initializes them itself.

     * In a constructor, prefer use of the member initialization list to 
    assignment inside the body of the constructor. List data members in
    the initialization list in the same order they’re declared in the class.

    * Avoid initialization order problems across translation units by replacing
    non-local static objects with local static objects.

*/