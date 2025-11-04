#include <iostream>
#include <vector>
#include <stdexcept>


class MCEngine
{
public:
    MCEngine(){}
    void runSimulation()
    {
        std::cout << "MCEngine running simulation...\n";
        throw std::runtime_error("Simulation failed due to invalid parameters.");
    }

    void write()
    {
        std::cout << "Trying to write results...\n";
        throw std::runtime_error("Failed to write results to file.");
    }
    ~MCEngine()
    {
        std::cout << "Calling MCEngine destructor...\n";
        // Simulate exception
        write();
    }

};
/*
If we put a throw inside a destructor, we get a warning as destructors have non-throwing exception specification.

warning: '~MCEngine' has a non-throwing exception specification but can still throw [-Wexceptions]
throw std::runtime_error("Some exception");
note: destructor has a implicit non-throwing exception specification ~MCEngine()

However, if we embed such error within a function called from the destructor, the compiler won't even complain 
with a warning.
*/

void run()
{
    std::vector<MCEngine> mces(10);
    for(auto& mce : mces)
    {
        mce.runSimulation();
    }
}

int main()
{
    try
    {
        run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "[main] Caught exception" << e.what() << "\n";
    }
    std::cout << "[main] Program ended.\n";
    return 0;
}

/* all other MCEngines are never destroyed, as only the first one calls the destructor, but it has an 
uncaught exception and the program terminates. */