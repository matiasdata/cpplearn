#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <chrono>

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
    std::string encrypted{password}; // encrypted is created as late as possible. It is not created if there is an exception.
    encrypt(encrypted);
    return encrypted;
}

template <typename T>
void approachA(const std::vector<T>& data)
{
    T obj; // 1 ctor call
    for(auto& val : data)
    {
        obj = val; // n assignments
    }
    // 1 dtor call
}

template <typename T>
void approachB(const std::vector<T>& data)
{
    
    for(auto& val : data)
    {
        T obj{val}; // n ctor + n dtor calls
    }
}

using Clock = std::chrono::high_resolution_clock;

int main()
{
    try
    {
        std::cout << encryptPassword("envelope") << "\n";
        std::cout << encryptPassword("securepass") << "\n";
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
    // Case 1: std::string (cheap allocation due to small string optimization, otherwise can be slow).
    constexpr int N = 10000;
    std::vector<std::string> strings(N);
    for (int i = 0; i < N; ++i)
    {
        strings[i] = "Example_" + std::to_string(i);
        //strings[i] = "This_is_a_very_long_password_string_that_definitely_exceeds_SSO_example" + std::to_string(i);
        // with short string performance is similar, with long one approachB gets worse.
    }
    
    auto t1 = Clock::now();
    approachA(strings);
    auto t2 = Clock::now();
    approachB(strings);
    auto t3 = Clock::now();

    std::cout << "Strings - Approach A time: " << std::chrono::duration<double>(t2 - t1).count() << "s\n";
    std::cout << "Strings - Approach B time: " << std::chrono::duration<double>(t3 - t2).count() << "s\n";

    // Case 2: std::vector<int> (ctor and dtor are expensive because they are doing memory allocation in the heap).
    // in contrast, in approachA the same memory allocated (and deallocated) once is reused and no expensive ctor/dtor 
    // calls are performed inside each loop as in approachB.
    std::vector<std::vector<int>> vectors(N);
    for (int i = 0; i < N; ++i)
    {
        vectors[i] = std::vector<int>(100,i);
    }
    
    t1 = Clock::now();
    approachA(vectors);
    t2 = Clock::now();
    approachB(vectors);
    t3 = Clock::now();

    std::cout << "Vectors - Approach A time: "
              << std::chrono::duration<double>(t2 - t1).count() << "s\n";
    std::cout << "Vectors - Approach B time: "
              << std::chrono::duration<double>(t3 - t2).count() << "s\n";
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