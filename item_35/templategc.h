#include <iostream>

namespace TemplateApproach
{

class GameCharacter
{
public:
    GameCharacter(int Health_ = 100) : Health{Health_} {}
    int healthValue() const
    {
        preHealthCheck(); // do before stuff
        int val = doHealthValue(); // do the real work
        postHealthCheck(); // do after stuff
        return val;
    }
protected:
    virtual int doHealthValue() const 
    {
        return Health; // default algorithm for calculating character's health.
    }
private:
    int Health;
    void preHealthCheck() const  { }//std::cout << "[Before health check]\n"; }
    void postHealthCheck() const { }//std::cout << "[After health check]\n";  }
};

class Warrior : public GameCharacter
{
public:
    Warrior(int Strength_) : GameCharacter{100}, Strength{Strength_} {}
private:
    int doHealthValue() const override { return GameCharacter::doHealthValue()-Strength;} // override health calculation.
    int Strength;
};


} // namespace TemplateApproach

/*

Use the non-virtual interface idiom (NVI idiom), a form of the
Template Method design pattern that wraps public non-virtual
member functions around less accessible virtual functions.

Non-Virtual Interface (NVI) Idiom:
    - Public non-virtual function (e.g., healthValue)
      calls a private/protected virtual function (e.g., doHealthValue).
    - Pattern: Template Method (implementation is done in derived classes, base class can provide default implementation).
    - Derived classes redefine the private virtual, not the wrapper.
    - Benefits:
        * Allows consistent "before" and "after" processing (logging, checks, locking).
        * Keeps control over when virtual functions are called.
    - Drawbacks:
        * Still uses virtual dispatch.
        * Slightly more boilerplate.

*/