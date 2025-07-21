#include <iostream>
#include <string>

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
    std::string get(){return text;}
private:
    std::string text;
};

int main()
{
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

    return 0;
}