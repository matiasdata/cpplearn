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

// inefficient, does not initialize variables thus default initializers are called and then they are copy assigned.
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
    ABEntry me("Matias","416 Manchester Road",{4407469658107});
    me.consult();

    ABEntry mom("Viviana","Espinosa 2136",{5491169434314,541145813832});
    mom.consult();
    return 0;
}
/*
with the inefficient constructor
ABEntry theEntry("Matias","416 Manchester Road",{4407469658107});
prints:
Called MyString default constructor
Called MyString default constructor
Called MyString constructor
Called MyString Copy assignment
Called MyString destructor
Called MyString constructor
Called MyString Copy assignment
Called MyString destructor

1) the strings theName and theAddress are default constructed as empty strings.
2) the std::string name is used to create a MyString by calling the ctor that takes a string,
3) theName is copy assigned to this string
4) the auxiliary MyString is destructed.
5) the std::string address is used to create a MyString by calling the ctor that takes a string,
6) theAddress is copy assigned to this string
7) the auxiliary MyString is destructed.


whit the efficient constructor
ABEntry theEntry("Matias","416 Manchester Road",{4407469658107});
prints:
Called MyString constructor
Called MyString constructor

*/