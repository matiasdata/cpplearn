#include <iostream>
#include <memory>
#include <mutex>
#include <string>

class Lock
{
public:
    explicit Lock(std::mutex& rm) : mtxPtr{&rm} 
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
    std::mutex* mtxPtr;
};

int main()
{
    {
        std::mutex m;
        Lock lock1(m);
        // Lock lock2(lock1); // error
        // Lock lock2 = lock1; // error
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