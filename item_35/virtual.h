#include <iostream> 

namespace VirtualApproach
{
class GameCharacter
{
public:
    GameCharacter(int Health_ = 100) : Health{Health_} {}
    int virtual healthValue() const {return Health;} // default implementation
private:
    int Health;
};

class Warrior : public GameCharacter
{
public:
    Warrior(int Strength_) : GameCharacter{100}, Strength{Strength_} {}
    int healthValue() const {return GameCharacter::healthValue()-Strength;}
private:
    int Strength;
};

} // namespace VirtualApproach
