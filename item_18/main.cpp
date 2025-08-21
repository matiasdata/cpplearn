#include <iostream>
#include <cstdio>

// BAD INTERFACE

// class Socket
// {
// public:
//     Socket(int type); // suppose type has to be 1 or 2 depending on the type of socket. No clear meaning
// };

// GOOD INTERFACE

class Socket
{
public:
    static Socket tcp() {return Socket(Protocol::TCP);}
    static Socket udp() {return Socket(Protocol::UDP);}
    void print()
    {
        if (protocol == Protocol::TCP)
        {
            std::cout << "TCP";
        }
        else
        {
            std::cout << "UDP";
        }
        std::cout << "\n";
    }
private:
    enum class Protocol {TCP, UDP};
    explicit Socket(Protocol p) : protocol{p} {}
    Protocol protocol;
};

// Safe RAII wrapper
struct FileCloser
{
    FileCloser(){std::cout << "Calling FileCloser constructor\n";}
    ~FileCloser(){std::cout << "Calling FileCloser destructor\n";}
    void operator()(FILE* f) const 
    {
        if (f)
        { 
            std::cout << "Calling fclose on the file\n";
            fclose(f);
        }
    }
};

using FileHandle = std::unique_ptr<FILE,FileCloser>;
// The second parameter to the unique_ptr (FileCloser) is the deleter type, which defines how the resource should be freed.

int main()
{
    Socket s1 = Socket::tcp();
    Socket s2 = Socket::udp();
    s1.print();
    s2.print();
    // Socket s3(2); // error
    FileHandle f(fopen("data.txt", "r"));
    // File is always closed, even if exception is thrown.
}

/*

In C++ there’s no semantic difference between struct and class except:
    * By default, members in a struct are public.
    * By default, members in a class are private.

General Patterns:
    * Use strong types, enums, wrappers → avoids "magic numbers" and wrong argument order.
    * RAII → makes cleanup automatic.
    * Factory functions → prevent misuse of constructors.
    * Check invariants at construction → no invalid objects possible.
    * Descriptive names & overloads → guide correct usage.
    * Make it hard to misuse (wrong order, invalid values, forgetting invariants).
    * Encourage correctness by construction (invalid states unrepresentable).
    * Prefer constexpr and compile-time checks where possible.

Key Takeaways: 
    * Good interfaces are easy to use correctly and hard to use incorrectly.
    * You should strive for these characteristics in all your interfaces.
    * Ways to facilitate correct use include consistency in interfaces and
    behavioral compatibility with built-in types.
    * Ways to prevent errors include creating new types, restricting opera-
    tions on types, constraining object values, and eliminating client re-
    source management responsibilities.
    * std::shared_ptr supports custom deleters. This prevents the cross-
    DLL problem, can be used to automatically unlock mutexes (see
    Item 14), etc.
*/