#include <iostream>
#include <string>


class AllocationMetrics
{
public: 
    static uint64_t CurrentUsage(){return TotalAllocated-TotalFreed;}
    static void allocated(size_t size){TotalAllocated+=size;}
    static void freed(size_t size){TotalFreed+=size;}
private:
    inline static uint64_t TotalAllocated{0};
    inline static uint64_t TotalFreed{0};
};


void PrintMemoryUsage()
{
    std::cout << "Memory usage: " << AllocationMetrics::CurrentUsage() << "\n";
}

void* operator new(std::size_t size)
{
    AllocationMetrics::allocated(size);
    return malloc(size);
}

void operator delete(void* memory, std::size_t size) noexcept
{
    AllocationMetrics::freed(size);
    free(memory);
}


struct Object
{
    int x, y, z;
};

int main()
{
    Object* obj = new Object;
    PrintMemoryUsage();
    std::string name = "Matias";
    PrintMemoryUsage();
    {
        std::string longname = "This is a really long string that will likely exceed the SSO buffer and trigger allocation.";
        PrintMemoryUsage();
    }
    PrintMemoryUsage();
    obj->x = 1;
    return 0;
}

// AllocationMetrics uses only static methods and data.
// No instance of the class is ever created.
// Static data (TotalAllocated/Freed) is shared globally across the program.
// Static methods can be called via class name without any object.
// `inline static` (C++17) allows definition inside the header directly.

// The constructor of AllocationMetrics is never called,
// because no instance of the class is ever created.
// All members used are static, accessed via the class itself.
// Constructors only run when an object is constructed — which we never do.

/*
Old C++ (before C++17)

class AllocationMetrics
{
public: 
    static uint64_t CurrentUsage(){return TotalAllocated-TotalFreed;}
    static void allocated(size_t size){TotalAllocated+=size;}
    static void freed(size_t size){TotalFreed+=size;}
private:
    static uint64_t TotalAllocated; // could not define here
    static uint64_t TotalFreed;
};

// usually in another .cpp file, otherwise you get linker errors
uint64_t AllocationMetrics::TotalAllocated = 0;
uint64_t AllocationMetrics::TotalFreed = 0;

// now you can include that definitions in the header file (header only),
but also you can initialize with inline static inside the class.
*/
