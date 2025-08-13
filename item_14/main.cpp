#include <iostream>
#include <memory>
#include <mutex>
#include <string>

/* Prohibit Copying */

class Lock
{
public:
    explicit Lock(std::mutex& rm) : mtxPtr{&rm} // explicit prevents any implicit conversions, must be called via direct call.
    {
        mtxPtr->lock(); // acquire the resource
        std::cout << "Mutex locked\n";
    }
    // what should happen when a RAII object is copied.
    // 1st option: Prohibit copying, could inherit from Uncopyable (from Item 6)
    Lock(const Lock&) = delete; // delete copy ctor 
    Lock& operator=(const Lock&) = delete; // delete copy assignment operator
    ~Lock()
    {
        mtxPtr->unlock(); // release the resource
        std::cout << "Mutex unlocked\n";
    }
    
private:
    std::mutex* mtxPtr; // could also use a reference
};

/* Reference counting */

class SharedFile
{
public:
    explicit SharedFile(const std::string& name) : filePtr{std::make_shared<std::string>(name)} {}
    void print() const 
    {
        std::cout << "Shared file: " << *filePtr << " (owners: " << filePtr.use_count() << ")\n";
    }
private:
    std::shared_ptr<std::string> filePtr;

};

int main()
{
    // 1. Prohibit copying
    {
        std::mutex m;
        Lock lock1(m);
        // Lock lock2(lock1); // error
        // Lock lock2 = lock1; // error
    }
    // 2. Reference counting
    {
        SharedFile f1("report.txt");
        SharedFile f2 = f1; // shares the same file
        f1.print();
        f2.print();
    }
}


/*
================ Summary =================
When designing RAII classes, define clear copying behavior:

1. Prohibit copying:
   - Delete copy constructor/assignment if multiple ownership makes no sense.

2. Reference counting:
   - Use std::shared_ptr for shared ownership, resource freed when last owner dies.

3. Deep copy:
   - Allocate a new resource when copying, so each object owns its own copy.

4. Transfer ownership:
   - Use move semantics (std::unique_ptr) to hand off the resource.

Best practice:
- Decide copying policy early; default compiler-generated copy might not be correct.
===========================================
*/