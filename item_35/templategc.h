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
    void preHealthCheck() const  { std::cout << "[Before health check]\n"; }
    void postHealthCheck() const { std::cout << "[After health check]\n";  }
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