#include <iostream>
#include <cstring>

class String
{
public:
    String() = default;

    String(const char* string)
    {
        std::cout << "Created!\n";
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data,string, m_Size);
    }

    String(const String& other)
    {
        std::cout << "Copied!\n";
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data,other.m_Data, m_Size);
    }

    String(String&& other)
    {
        std::cout << "Moved!\n";
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        other.m_Size = 0;
        other.m_Data = nullptr;
    }

    ~String()
    {
        std::cout << "Destroyed!\n";
        delete[] m_Data;
        m_Data = nullptr;
        m_Size = 0;
    }

    void Print()
    {
        for(uint32_t i = 0; i < m_Size; ++i)
        {
            std::cout << m_Data[i];
        }
        std::cout << "\n";
    }

private:
    char* m_Data;
    uint32_t m_Size;
};




class EntityRef
{
public:
    EntityRef(String& name) : m_Name(name) {}
    //Entity(String&& name) : m_Name((String&&) name) {}

    void PrintName()
    {
        m_Name.Print();
    }

private:
    String& m_Name;
};

class EntityMov
{
public:
    EntityMov(const String& name) : m_Name(name) {}
    EntityMov(String&& name) : m_Name((String&&) name) {}

    void PrintName()
    {
        m_Name.Print();
    }

private:
    String m_Name;
};

int main()
{   
    {
        String myName("Matias");
        EntityRef myEntityRef(myName);
        myEntityRef.PrintName();
        
    }
    std::cout << "Out of first scope\n";
    {
        EntityMov myEntityMov("Matias");
        myEntityMov.PrintName();

    }
    std::cout << "Out of second scope\n";
    std::cin.get();
}

