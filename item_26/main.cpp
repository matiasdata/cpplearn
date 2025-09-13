#include <iostream>
#include <stdexcept>
#include <string>


constexpr size_t MinimumPasswordLength = 8;

void encrypt(std::string& s)
{
    for(char& c : s) c++; // trivial encryption
}

std::string encryptPassword(const std::string& password)
{
    if(password.length() < MinimumPasswordLength)
    {
        throw std::invalid_argument("Password is too short");
    }
    std::string encrypted{password};
    encrypt(encrypted);
    return encrypted;
}

int main()
{
    try
    {
        std::cout << encryptPassword("envelope") << "\n";
        std::cout << encryptPassword("secure") << "\n";
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

/*

Postpone variable definitions until the moment of use:
1. Avoid constructing and destructing objects you never use
   (e.g., when an exception is thrown before the variable is needed).
2. Prefer initialization over default construction + assignment:
     std::string s(password);  // better than default + assignment
3. Improves clarity: variables are defined close to where their meaning is obvious.
4. In loops, weigh trade-offs:
     - Define outside loop: 1 ctor + 1 dtor + n assignments
     - Define inside loop: n ctors + n dtors
   Prefer inside-loop definitions unless assignment is clearly cheaper
   and performance is critical.
Rule of thumb: define variables as late as possible, with
   meaningful initialization arguments, and in the smallest scope.

*/