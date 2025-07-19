#include <iostream>
#include <string>

template <typename Derived>
class InstanceCounter
{
public:
    InstanceCounter() {++count;}
    InstanceCounter(const InstanceCounter& other) {++count;}
    ~InstanceCounter(){--count;}
    static size_t getCount(){
        return count;
    }

private:
    inline static size_t count{0};
};

// template <typename Derived>
// size_t InstanceCounter<Derived>::count{0};

class Bond : public InstanceCounter<Bond> 
{
public:
    Bond(std::string name_) : name{name_}{}
private:
    std::string name;
};

class Equity : public InstanceCounter<Equity> 
{
public:
    Equity(std::string name_) : name{name_}{}
private:
    std::string name;
};

// Second example 
template <typename Derived>
class Base
{
public:

    void compute(double& x)
    {
        static_cast<Derived*>(this)->impl(x);
    }
protected:
    Base() = default; 
    // constructor is protected to prohibit the creation of Base objects, so that it is accessible to derived classes.
};

class addOne : public Base<addOne>
{
public:
    addOne(){};
    void impl(double& x){x += 1.0;}
};

class multTwo : public Base<multTwo>
{
public:
    multTwo(){};
    void impl(double& x){x *= 2.0;}
};


// Third example
template <typename Derived>
class Animal
{
public:
    void make_sound() const
    {
        std::cout << "The animal is about to make a sound:\n";
        static_cast<const Derived&>(*this).impl();
    }
protected:
    Animal() = default;
};

class Cow : public Animal<Cow>
{
public:
    void impl() const{std::cout << "moo\n";}
};

class Sheep : public Animal<Sheep>
{
public:
    void impl() const{std::cout << "baa\n";}
};

template <typename Derived>
void print(Animal<Derived> animal)
{
    animal.make_sound();
}




int main()
{
    // first example
    Bond b1("UST10Y");
    Bond b2("FR2Y");
    Equity e1("BA");
    std::cout << "Bond count: " << Bond::getCount() << "\n";
    std::cout << "Equity count: " << Equity::getCount() << "\n";
    Bond b3("UK5Y");
    Equity e2("AMZN");
    std::cout << "Bond count: " << Bond::getCount() << "\n";
    std::cout << "Equity count: " << Equity::getCount() << "\n";

    // second example
    double x = 4.0;
    std::cout << "x = " << x  << "\n";
    addOne addOneCalc;
    multTwo multTwoCalc;
    addOneCalc.compute(x); // calls the compute implementation defined in the subclass addOne
    std::cout << "x = " << x  << "\n";
    multTwoCalc.compute(x); // calls the compute implementation defined in the subclass multTwo
    std::cout << "x = " << x  << "\n";

    // third example
    Cow betty;
    Sheep roshi;
    betty.make_sound();
    roshi.make_sound();
    print(betty);
    print(roshi);
}


/*
===============================
  Curiously Recurring Template Pattern (CRTP)
===============================

CRTP is a C++ idiom where a class `Derived` inherits from a template base class
`Base<Derived>`. It enables static (compile-time) polymorphism without the
overhead of virtual functions.

Pattern:
    template<typename Derived>
    class Base {
        // Use static_cast<Derived*>(this) for derived-specific behavior
    };

    class Derived : public Base<Derived> { };

Key Use Cases:
- Enforcing interfaces at compile-time (no need for virtuals)
- Static counters/logging per derived type
- Static polymorphism for performance (e.g. avoiding vtables)
- Code reuse in base while maintaining derived-type awareness

Main Benefits:
- Zero runtime cost (no virtual dispatch)
- Type-safe behavior injection
- Compile-time optimizations possible

Caveats:
- Not true polymorphism (no dynamic dispatch)
- Code bloat possible with many instantiations
*/


// In C++17+, use 'inline static' for static data members in templates
// to allow header-only definition and avoid linker errors.
// Without 'inline', define the static member out-of-line in a .cpp file.
// alternatively (old style), use this:
// template <typename Derived>
// size_t InstanceCounter<Derived>::count{0};