#include <iostream>
#include <algorithm>

// Payoff is a polymorphic base class because it declares virtual functions
// (operator() and clone) and is intended to be used via base class pointers.
// According to Item 7, such classes MUST have a virtual destructor to ensure
// derived destructors are called correctly when deleting via a base pointer.

class Payoff
{
public:
    Payoff() = default; // allows derived classes to construct Payoff
    virtual double operator()(double Spot) const = 0;
    // Pure virtual function makes this an abstract class — typical for polymorphic use.
    virtual Payoff* clone() const = 0;
    // clone is also virtual — used for polymorphic copying.
    
    virtual ~Payoff() = 0;     
    // Virtual destructor is essential! Without it, deleting a derived object
    // (e.g., PayoffCall or PayoffPut) through a Payoff* leads to undefined behavior.
private:
};

Payoff::~Payoff() {} // virtual destructor needs to be declared




class PayoffCall : public Payoff
{
public:
    PayoffCall(double Strike_) : Strike{Strike_} {}
    virtual inline double operator()(double Spot) const override
    {
        return std::max(Spot-Strike,0.0);
    }
    virtual Payoff* clone() const override
    {
        return new PayoffCall(*this);
    }
    virtual ~PayoffCall() override {};
    // Virtual destructor is needed to be declared, as the base class has a pure virtual destructor,
    // in a case like this, one could define the base destructor and not override it.

private:
    double Strike;
};

class PayoffPut : public Payoff
{
public:
    PayoffPut(double Strike_) : Strike{Strike_} {}
    virtual inline double operator()(double Spot) const override
    {
        return std::max(Strike-Spot,0.0);
    }
    virtual Payoff* clone() const override
    {
        return new PayoffPut(*this);
    }
    virtual ~PayoffPut() override {};

private:
    double Strike;
};


int main()
{
    Payoff* ppc = new PayoffCall(100.0);
    Payoff* ppp = new PayoffPut(100.0);
    double Spot = 120;
    std::cout << "Payoff Call at Spot = 120: " << ppc->operator()(Spot) << "\n";
    std::cout << "Payoff Put at Spot = 120: " << ppp->operator()(Spot) << "\n";

    Spot = 90;
    std::cout << "Payoff Call at Spot = 90: " << ppc->operator()(Spot) << "\n";
    std::cout << "Payoff Put at Spot = 90: " << ppp->operator()(Spot) << "\n";

    // Safe deletion via base pointer due to virtual destructor
    delete ppc;
    delete ppp;
    // deleting derived objects via base pointers without a virtual destructor leads to undefined behavior.
}