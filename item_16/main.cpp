#include <iostream>


class Chatty
{
public:
    Chatty(){std::cout << "Constructor called!\n";}
    ~Chatty(){std::cout << "Destructor called!\n";}
};

int main()
{
    std::cout << "Now calling ctor of arrc!\n";
    Chatty arrc[3]; // no problem because this are statically allocated.

    std::cout << "=== Correct usage: new + delete ===\n";
    Chatty* pc = new Chatty{}; // single object
    delete pc;  // correct: matches "new"

    std::cout << "\n=== Correct usage: new[] + delete[] ===\n";
    Chatty* parrc = new Chatty[3]; // array of 3 objects
    delete[] parrc; // correct: delete[] matches "new[]"

    // std::cout << "\n=== Incorrect usage: new[] + delete ===\n";
    // Chatty* parrc2 = new Chatty[3]; // array of 3 objects
    // delete parrc2; // incorrect: delete does not match "new[]" -> undefined behavior, usually memory leaks

    // std::cout << "\n=== Incorrect usage: new + delete[] ===\n";
    // Chatty* p2 = new Chatty{}; // array of 3 objects
    // delete[] p2; // incorrect: delete[] does not match "new" -> undefined behavior, tries to destroy several objects (even more dangerous)

    std::cout << "Now calling dtor of arrc!\n";
}

/* When in new[] + delete, the compiler issues a warning, a very clear one:
main.cpp:25:5: warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'? [-Wmismatched-new-delete]
   25 |     delete parrc2; // incorrect: delete does not match "new[]" -> undefined behavior, usually memory leaks
      |     ^
      |           []
main.cpp:24:22: note: allocated with 'new[]' here
   24 |     Chatty* parrc2 = new Chatty[3]; // array of 3 objects
      |                      ^
1 warning generated.
If one runs the executable it produces an error and aborts:
    main(63043,0x1ef011f00) malloc: *** error for object 0x600001835230: pointer being freed was not allocated
    main(63043,0x1ef011f00) malloc: *** set a breakpoint in malloc_error_break to debug
    zsh: abort      ./main


When in new + delete[], the compiler issues a warning as well:
main.cpp:29:5: warning: 'delete[]' applied to a pointer that was allocated with 'new'; did you mean 'delete'? [-Wmismatched-new-delete]
   29 |     delete[] p2; // incorrect: delete[] does not match "new" -> undefined behavior, tries to destroy several objects (even more dangerous)
      |     ^     ~~
main.cpp:28:18: note: allocated with 'new' here
   28 |     Chatty* p2 = new Chatty{}; // array of 3 objects
      |                  ^
1 warning generated.

In this case the result would likely be as follows:
delete would read some memory and interpret what it read as an array
size, then start invoking that many destructors, oblivious to the fact
that the memory it’s working on not only isn’t in the array, it’s also
probably not holding objects of the type it’s busy destructing.

*/