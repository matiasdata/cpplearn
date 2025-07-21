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
    char& operator[](std::size_t position) const {return pText[position];} //inappropriate, but bitwise const legitimate
    std::string get() const {return static_cast<std::string>(pText);} 
private:
    char* pText{nullptr}; // a const CTextBlock could still modify the pText contents 
    // because while the pointer will be const, it will not point to constant data.
    std::size_t textLength{0};
    bool lengthIsValid{false};
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

    const CTextBlock tbc("Hello");
    std::cout << "tbc: " << tbc.get() << "\n";
    std::cout << "Modifying tbc." << "\n";
    tbc[1] = 'a';
    std::cout << "Updated tbc: " << tbc.get() << "\n";
    return 0;
}