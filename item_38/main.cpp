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

template <typename T>
class BadSet : public std::list<T>
{
public:
    bool member(const T& value) const
    {
        return std::find(this->begin(),this->end(),value) != this->end(); 
        // std::find is a standard library algorithm that takes an iterator, loops until it reaches the end searching for a value.
    }
    void insert(const T& value)
    {
        if(!member(value))
        {
            this->push_back(value);
        } // only inserts the new value if it is not already on the set.
    }
    void remove(const T& value)
    {
        auto it = std::find(this->begin(),this->end(),value);
        if(it != this->end())
        {
            this->erase(it);
        } // erase a value if it is in the set.
    }
};

template <typename T>
class Set
{
public:
    bool member(const T& value) const
    {
        return std::find(rep.begin(),rep.end(),value) != rep.end(); 
        // std::find is a standard library algorithm that takes an iterator, loops until it reaches the end searching for a value.
    }
    void insert(const T& value)
    {
        if(!member(value))
        {
            rep.push_back(value);
        } // only inserts the new value if it is not already on the set.
    }
    void remove(const T& value)
    {
        auto it = std::find(rep.begin(),rep.end(),value);
        if(it != rep.end())
        {
            rep.erase(it);
        } // erase a value if it is in the set.
    }
    void print() const
    {
        std::cout << "{ ";
        for(const auto& x : rep) std::cout << x << ", ";
        std::cout << "}\n";
    }
private:
    std::list<T> rep;
};

int main() {
    std::cout << "=== Example 1: 'has-a' Relationship ===\n";
    Person alice("Alice",
                 Address("42 Maple St", "Springfield"),
                 PhoneNumber("555-1234"));
    alice.printInfo();

    std::cout << "\n=== Example 2: 'is-implemented-in-terms-of' Relationship ===\n";
    BadSet<int> bad;
    bad.insert(1);
    bad.insert(2);
    bad.push_back(1); // Still allowed! Breaks uniqueness. BadSet is-a list, thus inherits all its functions!
    std::cout << "BadSet (inherits from list) allows duplicates: ";
    for (int x : bad) std::cout << x << " ";
    std::cout << "\n";

    Set<int> good;
    good.insert(1);
    good.insert(2);
    good.insert(1); // Ignored.
    // good.push_back(1); //error, Set does not inherit functions from lists, Set is-implemented-in-terms-of lists!
    std::cout << "Set (composed of list) enforces uniqueness: ";
    good.print();
}

/*
===============================================================================
 Summary:
===============================================================================
✔ Composition expresses relationships different from inheritance.

   • "has-a" → application domain.
       Example: Person has-a Address.

   • "is-implemented-in-terms-of" → implementation domain.
       Example: Set is implemented in terms of std::list.

✔ Use public inheritance only for “is-a”.
✔ Use composition when:
      - You only want to reuse implementation, not interface.
      - Derived behavior differs from the base.
      - The relationship models ownership or containment.

→ Rule: Prefer composition over inheritance when relationships
  are not “is-a”.
===============================================================================
*/