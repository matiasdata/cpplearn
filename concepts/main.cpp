#include <iostream>
#include <concepts>

/*
Recall the following example from the CRTP:
template <typename Derived>
class Animal
{
public:
    void make_sound() const
    {
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

We aim to do this instead with Concepts
*/

class AnimalTag{}; 
// AnimalTag is an empty class, only to guarantee we are creating an Animal and not
// just a class with a make_sound() function, which could be say a musical instrument

template <typename T>
concept Animal = 
    requires (T animal) {animal.make_sound();} &&
    std::derived_from<T,AnimalTag>;



template <Animal T>
void print(const T& animal)
{
    animal.make_sound();
}

// syntactic sugar version instead of templatized code.
void printauto(Animal auto const& animal)
{
    animal.make_sound();
}

class Cow : public AnimalTag
{
public:
    void make_sound() const{std::cout << "moo\n";}
};

class Sheep : public AnimalTag
{
public:
    void make_sound() const{std::cout << "baa\n";}
};

int main()
{
    Cow betty;
    Sheep roshi;
    print(betty);
    print(roshi);
    printauto(betty);
    printauto(roshi);
}