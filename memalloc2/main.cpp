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

// Your global operator new only captures explicit `new` allocations.
// std::string may not allocate heap memory due to Small String Optimization (SSO).
// Use a longer string to force dynamic memory allocation and test your hook.
