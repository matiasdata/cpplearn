#include <iostream>
#include <vector>  
#include <list>
#include <iterator>


template <typename T>
void print2nd(const T& container)
{
    if (container.size() >= 2)
    {
        typename T::const_iterator iter = container.begin();
        ++iter;
        std::cout << "Second element: " << *iter << "\n";
    }
}

/*
If we miss the typename the compiler will throw an error as it cannot parse this statement (it is ambiguous).
 error: missing 'typename' prior to dependent type name 'T::const_iterator'
   12 |         T::const_iterator iter = container.begin();
      |         ^~~~~~~~~~~~~~~~~
      |         typename 
1 error generated.
*/

int main()
{
    std::cout << "Use of typename for nested dependent typenames.\n";
    std::vector<int> v{1,2,3};
    std::list<int> l{3,4,5};
    print2nd(v);
    print2nd(l);
    
    
}