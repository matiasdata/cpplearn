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
int loseHealthSlow(const GameCharacter&){return 200;}
} // namespace StratFunApproach