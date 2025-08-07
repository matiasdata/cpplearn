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
        // if(str == other) return *this; // key line: handle self assignment in operator= (one could potentially be using the same char*)
        // delete[] str;
        // size_t len = strlen(other);
        // str = new char[len+1];
        // strcpy(str,other);
        // return *this;
        char* pOrig = str; // alternative: do a manual swap, this can be exception safe if new throws an exception.
        size_t len = strlen(other);
        str = new char[len+1];
        strcpy(str,other);
        delete[] pOrig;
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

template <typename T>
class NamedObject
{
public: 
    NamedObject() : name{}, obj{nullptr} {}
    NamedObject(std::string name_, const T& obj_) : name{name_}, obj{new T(obj_)} {}
    NamedObject(const NamedObject& other) : name{other.name}, obj{new T(*(other.obj))} {}
    // NamedObject& operator=(const NamedObject& other)
    // {
    //     // alternative 3: copy and swap
    //     NamedObject temp(other); // make a local (temporary) copy of other's data
    //     swap(temp); // swap *this's data with the copy's data; needs a swap member function.
    //     return *this;
    // }
    void swap(NamedObject& other)
    {
        std::swap(name, other.name);
        std::swap(obj,other.obj);
    }
    NamedObject& operator=(NamedObject other)
    {
        // alternative 4: more concise copy and swap
        swap(other); // since other was passed by value, it is already a copy
        return *this;
    }
    // one can declare only one operator=
    const std::string& getName(){return name;}
    const T& getObj(){return *obj;}

private:
    std::string name;
    T* obj;
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
    s = "Now my name is Slim Shady!";
    std::cout << s.get() << "\n";

    NamedObject<int> me("Matias",34);
    std::cout << "me: " << me.getName() << ", age: " << me.getObj() << "\n"; 
    NamedObject<int> mom("Viviana",75);
    std::cout << "mom: " << mom.getName() << ", age: " << mom.getObj() << "\n"; 
    me = mom;
    std::cout << "me: " << me.getName() << ", age: " << me.getObj() << "\n"; 

}

/*
Key Takeaways:
    * Make sure operator= is well-behaved when an object is assigned to
    itself. Techniques include comparing addresses of source and target
    objects, careful statement ordering, and copy-and-swap.
    * Make sure that any function operating on more than one object behaves
     correctly if two or more of the objects are the same.
*/