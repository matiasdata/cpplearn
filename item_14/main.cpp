#include <iostream>
#include <memory>
#include <mutex>
#include <string>

/* 1. Prohibit Copying */

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

/* 2. Reference counting */

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

/* 3. Deep Copy */

class DeepCopyBuffer
{
public:
    explicit DeepCopyBuffer(const std::string& data) : buffer{std::make_unique<std::string>(data)} {}
    // Deep copy
    DeepCopyBuffer(const DeepCopyBuffer& other) : buffer{ new std::string(*(other.buffer))} { }
    DeepCopyBuffer& operator=(const DeepCopyBuffer& other)
    {
        if (this != &other)
        {
            *buffer = *(other.buffer);
        }
        return *this;
    }
    void print() const { std::cout << "Buffer: " << *buffer << "\n"; }
private:
    std::unique_ptr<std::string> buffer;
};

/* 4. Transfer ownership */

class MovableResource
{
public:
    explicit MovableResource(const std::string& name) : resource{std::make_unique<std::string>(name)} {}

    // Move constructor
    MovableResource(MovableResource&& other) noexcept : resource{std::move(other.resource)} {}
    MovableResource& operator=(MovableResource&& other) noexcept
    {
        if (this != &other)
        {
            resource = std::move(other.resource);
        }
        return *this;
    }

    void print() const 
    {
        if (resource)
            std::cout << "Resource: " << *resource << "\n";
        else
            std::cout << "Resource moved away\n";
    }

private:
    std::unique_ptr<std::string> resource;

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

    // 3. Deep copy
    {
        DeepCopyBuffer b1("Hello");
        DeepCopyBuffer b2 = b1; // deep copy
        b1.print();
        b2.print();
    }

    // 4. Transfer ownership
    {
        MovableResource r1("DB Connection");
        MovableResource r2 = std::move(r1);
        r1.print();
        r2.print();
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