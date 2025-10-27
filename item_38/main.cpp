#include <iostream>
#include <list>
#include <algorithm>
#include <string>

class Address
{
public:
    Address(std::string street_, std::string city_) : street{std::move(street_)}, city{std::move(city_)} {}
    std::string full() const { return street + ", " + city;}
private:
    std::string street;
    std::string city;
};


class PhoneNumber {
public:
    PhoneNumber(std::string number_) : number(std::move(number_)) {}
    std::string str() const { return number; }
private:
    std::string number;
};


class Person
{
public:
    Person(std::string name_, Address address_, PhoneNumber phone_) : 
                                                                     name{std::move(name_)},
                                                                     address{std::move(address_)},
                                                                     phone{std::move(phone_)} {}
    void printInfo() const {
        std::cout << name << " lives at " << address.full()
                  << " and can be reached at " << phone.str() << "\n";
    }
private:
    std::string name; // Person *has-a* name.
    Address address; // Person *has-a* Address.
    PhoneNumber phone; // Person *has-a* PhoneNumber.
};

int main() {
    std::cout << "=== Example 1: 'has-a' Relationship ===\n";
    Person alice("Alice",
                 Address("42 Maple St", "Springfield"),
                 PhoneNumber("555-1234"));
    alice.printInfo();
}


/*
===============================================================================
 Item 38: Model "has-a" or "is-implemented-in-terms-of" through composition
===============================================================================
Composition occurs when one class contains objects of another class.

✔ Public inheritance → "is-a"
    • Derived must satisfy all properties of the base.
    • Example: A Rectangle is-a Shape.

✔ Composition → "has-a" or "is-implemented-in-terms-of"
    • "has-a": Relationship between *application domain* classes.
    • "is-implemented-in-terms-of": Relationship in the *implementation domain*,
      when one class uses another internally for functionality.
===============================================================================
*/