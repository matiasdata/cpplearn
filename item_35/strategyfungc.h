#include <iostream>
#include <functional>


namespace StratFunApproach
{

class GameCharacter
{
public:
    using HealthFunction = std::function<int(const GameCharacter&)>;
    explicit GameCharacter(HealthFunction hf = defaultHealthCalc) : healthCalc{std::move(hf)} {}
    int healthValue() const {return healthCalc(*this);}
private:
    HealthFunction healthCalc;
    static int defaultHealthCalc(const GameCharacter&){return 100;}
};

int loseHealthFast(const GameCharacter&){return 50;}
struct loseHealthSlow
{
    int operator()(const GameCharacter&) const {return 200;}
};
auto loseHealthSuperSlow = [] (const GameCharacter&) {return 1000;};

} // namespace StratFunApproach 


/*
Advantages:
  - Runtime flexibility: each instance can have its own behavior.
  - Works with lambdas, functions, functors, and member functions.
  - Very clean and modern (C++11+).
Drawbacks:
  - External functions can’t access private members unless made friends.
*/