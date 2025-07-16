#include <iostream>
#include <string>

void* operator new(std::size_t size)
{
    std::cout << "Allocated " << size << " bytes.\n";
    return malloc(size);
}

void operator delete(void* memory, std::size_t size) noexcept
{
    std::cout << "Freeing " << size << " bytes.\n";
    free(memory);
}

struct Object
{
    int x, y, z;
};

int main()
{
    Object* obj = new Object;
    std::string name = "Matias";
    {
        std::string longname = "This is a really long string that will likely exceed the SSO buffer and trigger allocation.";
    }
    obj->x = 1;
    return 0;
}

// Your global operator new only captures explicit `new` allocations.
// std::string may not allocate heap memory due to Small String Optimization (SSO).
// Use a longer string to force dynamic memory allocation and test your hook.
