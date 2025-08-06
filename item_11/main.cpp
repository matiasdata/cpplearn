#include <iostream>
#include <string>

class MyString
{
public:
    MyString()
    {
        str = new char[1];
        str[0] = '\0';
    }
    MyString(const char* str_)
    {
        if(str_ == nullptr)
        {
            str = new char[1];
            str[0] = '\0';
        } else {
            size_t len = strlen(str_);
            str = new char[len+1];
            strcpy(str,str_);
        }
    }
    MyString(const MyString& other) 
    {
        if(other.str)
        {
            size_t len = strlen(other.str);
            str = new char[len+1];
            strcpy(str,other.str);
        }
        else
        {
            str = new char[1];
            str[0] = '\0';
        }
    }
    MyString& operator=(const MyString& other)
    {
        if(this == &other) return *this; // key line: handle self assignment in operator=
        delete[] str;
        size_t len = strlen(other.str);
        str = new char[len+1];
        strcpy(str,other.str);
        return *this;
    }

    MyString& operator=(const char* other)
    {
        if(str == other) return *this; // key line: handle self assignment in operator= (one could potentially be using the same char*)
        delete[] str;
        size_t len = strlen(other);
        str = new char[len+1];
        strcpy(str,other);
        return *this;
    }

    ~MyString()
    {
        delete[] str;
    }
    const char* get() const {return str;}
private:
    char* str;
};


int main()
{
    MyString s("Hello, world!");
    MyString t("I'm Matias");
    MyString& sr = s;
    s = sr;
    std::cout << s.get() << "\n";
    s = t;
    std::cout << s.get() << "\n";
}

/*
Key Takeaways:
    * Make sure operator= is well-behaved when an object is assigned to
    itself. Techniques include comparing addresses of source and target
    objects, careful statement ordering, and copy-and-swap.
    * Make sure that any function operating on more than one object be-
    haves correctly if two or more of the objects are the same.
*/