#include <iostream>
#include <stdexcept>

class Widget
{
public:
    Widget(){std::cout << "Calling Widget constructor!\n";}
    ~Widget(){std::cout << "Calling Widget destructor!\n";}
};

int priority()
{
    std::cout << "Computing priority...\n";
    throw std::runtime_error("priority failed!"); // simulate exception
    return 1;
}

void processWidget(std::shared_ptr<Widget> pw, int pty)
{
    std::cout << "Processing Widget with Priority " << pty << "\n";
}

int main()
{
    try 
    {
        std::cout << "Bad: inline new inside processWidget\n";
        processWidget(std::shared_ptr<Widget>(new Widget()),priority());
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    // Widget is never destroyed 
    try 
    {
        std::cout << "Good: use standalone statement \n";
        std::shared_ptr<Widget> pw(new Widget);
        processWidget(pw,priority());
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    // Widget is destroyed.
}

/*

What happens?
In the bad version:
    * new Widget runs → Widget allocated.
    * priority() runs → throws exception.
    * Since the std::shared_ptr constructor hasn’t executed yet, the raw pointer is lost.
    * Memory leak: Widget is never destroyed.

In the good version:
    * new Widget runs and is immediately wrapped in a std::shared_ptr.
    * Then priority() runs → throws exception.
    * Since the shared_ptr already owns the Widget, its destructor runs and frees it properly.

Key takeaway:
    Store newed objects in smart pointers in standalone statements.
    Failure to do this can lead to subtle resource leaks when exceptions
    are thrown.

Output of the script:
Bad: inline new inside processWidget
Calling Widget constructor!
Computing priority...
Calling Widget destructor!
Exception: priority failed!
Good: use standalone statement 
Calling Widget constructor!
Computing priority...
Calling Widget destructor!
Exception: priority failed!

*/