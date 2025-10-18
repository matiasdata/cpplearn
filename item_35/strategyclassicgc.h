#include <iostream>
#include <memory>

namespace ClassicStrategyApproach
{
class GameCharacter;

class HealthCalculator
{
public:
    virtual int calc(const GameCharacter&) const {return 100;} // default implementation
    virtual ~HealthCalculator() = default;
};

class FastDecay : public HealthCalculator
{
    int calc(const GameCharacter&) const {return 50;}
};

class SlowDecay : public HealthCalculator
{
    int calc(const GameCharacter&) const {return 200;}
};

class GameCharacter
{
public:
    explicit GameCharacter(std::shared_ptr<HealthCalculator> hc) : hCalc{std::move(hc)} {}
    int healthValue() const {return hCalc->calc(*this);}
private:
    std::shared_ptr<HealthCalculator> hCalc;
};


} // namespace ClassicStrategyApproach

/*
Advantages:
  - Fully OO: each strategy can be extended via inheritance.
  - Common in design-pattern implementations.
Drawbacks:
  - More boilerplate (extra classes, heap allocation).
  - Still uses virtual dispatch indirectly.
*/