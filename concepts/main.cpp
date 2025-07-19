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

template <typename T>
concept Animal = 
    requires (T animal) {animal.make_sound();} &&
    std::derived_from<T,AnimalTag>;

void print(Animal auto const& animal)
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
}