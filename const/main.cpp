#include <iostream>
#include <string>
#include <vector>

class TextBlock
{
public:
    TextBlock(const std::string& str) : text{str} {}
    const char& operator[](std::size_t position) const
    {
        std::cout << "const operator[] Accessing index " << position << std::endl;
        if(position >= text.size())
        {
            throw std::out_of_range("Index out of range!");
        }
        return text[position];
    }
    
    char& operator[](std::size_t position)
    {
        std::cout << "non-const operator[] call via cast..." << std::endl;
        return const_cast<char&>(static_cast<const TextBlock&>(*this)[position]);
    }
    std::string get()const {return text;}
private:
    std::string text;
};


class CTextBlock
{
public:
    CTextBlock(const char* pText_) {
        if (!pText_) {
            pText = nullptr;
            textLength = 0;
            lengthIsValid = false;
        } else {
            textLength = std::strlen(pText_);
            lengthIsValid = true;
            pText = new char[textLength + 1];
            std::strcpy(pText, pText_);
        }
    }
    char& operator[](std::size_t position) const {return pText[position];} 
    //inappropriate, but bitwise const legitimate, to be appropriate its return 
    // type should be const char&, so that in this way we can't modify the contents.
    char& operator[](std::size_t position)
    {
        return const_cast<char&>(static_cast<const CTextBlock&>(*this)[position]);
    }
    std::string get() const {return static_cast<std::string>(pText);} 
private:
    char* pText{nullptr}; // a const CTextBlock could still modify the pText contents 
    // because while the pointer will be const, it will not point to constant data.
    std::size_t textLength{0};
    bool lengthIsValid{false};
};


int main()
{

    char greeting[] = "Hello, World";
    char * pd = greeting; // array decays to char*, non-const pointer to non-const data
    const char * pcd = greeting; // non-const pointer to const data, equivalent to char const * (it only matters that const is before *).
    char * const cpd = greeting; // const pointer to non-const data
    const char * const cpcd = greeting; // const pointer to const data, read from right to left.

    pd = new char[] {"Hello"}; // legal to modify pointer
    pd[1]='a'; // legal to modify contents
    std::cout << "pd: " << pd << "\n";
    pcd = new char[] {"Hello"}; // legal to modify pointer
    // pcd[1] = 'a'; // illegal to modify contents
    std::cout << "pcd: " << pcd << "\n";
    // cpd = new char[6] {"Hello"}; // illegal to modify pointer
    cpd[1] = 'a'; // legal to modify contents
    std::cout << "cpd: " << cpd << "\n";
    // cpcd = new char[]{"Hello"}; // illegal to modify pointer
    // cpcd[1] = 'a'; // illegal to modify contents
    std::cout << "cpcd: " << cpcd << "\n";

    std::vector<int> vec {1,2,3,4,5};

    const std::vector<int>::iterator it = vec.begin();
    *it = 10; // legal, it behaves like a const-pointer to non-const data (i.e. T* const where T=int), can modify its contents but not the pointer.
    // ++it; // illegal, behaves like a const-pointer to non-const data.
    std::cout << "vec[0]= " << vec[0] << "\n";

    std::vector<int>::const_iterator cit = vec.begin();
    // *cit = 10; // illegal, behaves like a pointer to const data (i.e. const T*).
    ++cit; // legal
    std::cout << "*cit = " << *cit << "\n";

    TextBlock tb("Hello");

    std::cout << "Read from non-const object:\n";
    std::cout << "tb[1] = " << tb[1] << "\n"; // should call non-const, which calls const

    std::cout << "\nWrite to non-const object:\n";
    tb[1] = 'a'; // modifying via non-const

    std::cout << "Updated tb: " << tb.get() << "\n";

    const TextBlock ctb("World");

    std::cout << "\nRead from const object:\n";
    std::cout << "ctb[1] = " << ctb[1] << "\n"; // should call const version

    // Uncommenting below line will cause a compilation error
    // because we're trying to write through a const object.
    // ctb[1] = 'x';

    const CTextBlock tbc("Hello");
    std::cout << "tbc: " << tbc.get() << "\n";
    std::cout << "Modifying tbc." << "\n";
    tbc[1] = 'a'; // notice that a constant CTextBlock can modify it's indirect contents because the pointer-to-char is of type
    // char * const (pointer is const, address can't be modified, due to CTextBlock being const), but it is not of type
    // const char * const, that would require the pointer-to-char being const char* by default, and would make its contents unmodifiable.
    // We would still be able to replace the data as the pointer is not constant, but this would require copying and modifying the copy.
    std::cout << "Updated tbc: " << tbc.get() << "\n";
    return 0;
}