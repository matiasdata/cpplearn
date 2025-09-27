#include <iostream>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

double squareNonInline(double x) {return x * x;}

inline double squareInline(double x) {return x * x;}

int main()
{
    constexpr int N = 1000000;
    volatile double result = 0.0;

    auto start1 = Clock::now();
    for(int i = 0; i < N; ++i)
    {
        result+= squareNonInline(i);
    }
    auto end1 = Clock::now();

    auto start2 = Clock::now();
    for(int i = 0; i < N; ++i)
    {
        result+= squareInline(i);
    }
    auto end2 = Clock::now();

    auto start3 = Clock::now();
    for(int i = 0; i < N; ++i)
    {
        result+= i * i;
    }
    auto end3 = Clock::now();
    // manual inlining



    std::chrono::duration<double> timeNonInline = end1-start1;
    std::chrono::duration<double> timeInline = end2-start2;
    std::chrono::duration<double> timeManualInline = end3-start3;
    std::cout << "Result = " << result << "\n";
    std::cout << "Non-inline time: " << timeNonInline.count() << "s\n";
    std::cout << "Inline time:     " << timeInline.count()   << "s\n";
    std::cout << "Manual inline time:     " << timeManualInline.count()   << "s\n";

    double (*pf)(double) = squareInline; 
    pf(3.0); // this call to squareInline will not be inlined, even if squareInline, because it is through a function pointer.
    squareInline(3.0); // this call will be inlined.
    return 0;

}

/*

This script shows that inlining not always improves performance, particularly as compilers already optimize
the code in -O2 or -O3 levels of optimization. Use:
g++ -O0 -fno-inline -Wall -std=c++20 main.cpp -o main
to run the script without any optimization. In this way squareNonInline stays a real function call, squareInline
 is only inlined because of the keyword inline, not because the compiler feels like it.

Key Takeaways:
    * Limit most inlining to small, frequently called functions. This facilitates
    debugging and binary upgradability, minimizes potential code
    bloat, and maximizes the chances of greater program speed.
    * Don’t declare function templates inline just because they appear in
    header files.
    * Use it cautiously: focus on the 20% hot paths of your program, not everywhere.

*/