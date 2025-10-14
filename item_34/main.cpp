#include <iostream>

class Airplane
{
public:
    Airplane() : planeId{counter} {counter++;}
    virtual void construct() = 0;
    virtual void fly() = 0;
    int planeID() const {return planeId;};
private:
    int planeId;
    static int counter;
};

int Airplane::counter = 0;

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
    void construct() {std::cout << "Constructing model C\n.";}
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