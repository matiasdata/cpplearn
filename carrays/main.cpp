#include <iostream>

void print(int* arr, unsigned long size)
{
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << "\n";
    }

}

int main()
{
    int arr[5]={0,1,2,3,4}; // allocate an array of five elements (on the stack)
    for(int i = 0; i < 5; ++i)
    { 
        std::cout << "arr[" <<i <<"]=" << arr[i];
        std::cout << " = " << "*(arr+" <<i <<")=" << *(arr+i) << "\n"; // pointer arithmetic (array decays to a pointer)
    }
    // for a type T, arrays decay to pointers T*, but arrays are not T*.
    int* ptr = arr; // legal as array decays to int*.
    // pointer arithmetic ptr[i] == *(ptr + i) is always defined, for all pointers.
    for(int i = 0; i < 5; ++i)
    {
        std::cout << "ptr[" <<i <<"]=" << ptr[i];
        std::cout << " = " << "*(ptr+" <<i <<")=" << *(ptr+i) << "\n"; // pointer arithmetic 
    }
    // However, size of an array is a well defined concept, not matching that of a T*.
    std::cout << "Size of the array arr: " << sizeof(arr) << " = 5 * sizeof(int) "<< "\n";
    std::cout << "Size of int* p: " << sizeof(ptr) << "\n";
    // reassignment of arrays is illegal, however pointers can be reassigned freely.

    // Arrays decay to pointers when passed to functions — you lose size info.
    print(arr,5);
    print(ptr,5);

    int x = 1;
    int* px = &x;
    std::cout << "px: " << px  << ", x: " << *px << "\n";
    std::cout << "px+1: " << px+1 << ", *(px+1): " << *(px+1) << "\n"; 
    // illegal px+1 is unassigned, gives undefined behavior. 

    return 0;
}