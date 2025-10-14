#include <iostream>

class Airplane
{
public:
    Airplane() : planeId{counter} {counter++;}
    virtual void construct() = 0;
    virtual void fly() = 0;
    int planeID() const {return planeId;}
// protected:    
//      void defaultFly(){std::cout << "Airplane default fly.\n";}
private:
    int planeId;
    static int counter;
};

int Airplane::counter = 0;

// define a default implementation for fly, this can be called by derived classes (explicitely) if they need a default implementation.
void Airplane::fly()
{
    std::cout << "Airplane default fly.\n";
}

class ModelA : public Airplane
{
public:
    void construct() {std::cout << "Constructing model A.\n";}
    void fly(){Airplane::fly();}
};

class ModelB : public Airplane
{
public:
    void construct() {std::cout << "Constructing model B.\n";}
    void fly(){Airplane::fly();}
};

class ModelC : public Airplane
{
public:
    void construct() {std::cout << "Constructing model C.\n";}
    void fly(){std::cout << "Model C fly.\n";}
};

int main()
{
    ModelA airplane_A;
    airplane_A.construct();
    airplane_A.fly();
    std::cout << "Airplane_A id: " << airplane_A.planeID() << "\n";
    ModelB airplane_B;
    airplane_B.construct();
    airplane_B.fly();
    std::cout << "Airplane_B id: " << airplane_B.planeID() << "\n";
    ModelC airplane_C;
    airplane_C.construct();
    airplane_C.fly();
    std::cout << "Airplane_C id: " << airplane_C.planeID() << "\n";
    ModelA airplane_A2;
    airplane_A2.construct();
    airplane_A2.fly();
    std::cout << "Airplane_A2 id: " << airplane_A2.planeID() << "\n";

}

/*

Key takeaways:
    * Inheritance of interface is different from inheritance of implementation.
    Under public inheritance, derived classes always inherit base interfaces.
    * Pure virtual functions specify inheritance of interface only.
    * Simple (impure) virtual functions specify inheritance of interface
    plus inheritance of a default implementation.
    * Non-virtual functions specify inheritance of interface plus inheritance
    of a mandatory implementation.

In order to prevent erroneously assign the default implementation of a virtual member
function to a derived class, one can declare all virtual functions as pure virtual
and nevertheless provide a default implementation. Then on each derived class, one 
needs to call the base class function (in this example we call Airplane::fly(), notice
the need to specify we refer to the base one). Alternatively, we can declare our member
function as pure virtual, and declare protected a member function that provides a default
implementation, and then derived classes can call this function if they want to use the 
default version.
*/