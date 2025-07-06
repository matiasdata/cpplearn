#include <iostream>

int main()
{
    int x(0); // initializer is in parentheses
    int y = 0; // initializer follows "="
    int z{0}; // initializer is in braces
    int w = { 0 }; // rare: initializer uses "=" and braces

    std::cout << "x,y,z,w: " << x << "," << y << "," << z  << "," << w << "\n";

    int x2(1.0); // implicit casting
    int y2 = 1.0; // implicit casting
    // int z2{1.0}; // error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing] int z2{1.0}; 
    int z2{1};
    int w2{x2 + y2 + z2};
    std::cout << "w2: " << w2 << "\n";
    return 0;
}
