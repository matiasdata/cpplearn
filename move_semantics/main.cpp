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

    void Print() const
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

class EntityCopy
{
public:
    EntityCopy(const String& name) : m_Name(name) {}

    void PrintName() const
    {
        m_Name.Print();
    }

private:
    String m_Name;
};

class EntityRef
{
public:
    EntityRef(const String& name) : m_Name(name) {}

    void PrintName() const
    {
        m_Name.Print();
    }

private:
    const String& m_Name;
};

class EntityPtr
{
public:
    EntityPtr(const String* name) : m_Name(name) {}

    void PrintName() const
    {
        m_Name->Print();
    }

private:
    const String* m_Name;
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
        std::cout << "Using EntityCopy\n";
        EntityCopy myEntityCopy("Matias");
        myEntityCopy.PrintName();
    }
    std::cout << "Out of first scope\n";

    
    
    {
        std::cout << "Using EntityRef\n";
        String myName("Matias");
        EntityRef myEntityRef(myName);
        myEntityRef.PrintName();
        
    }
    std::cout << "Out of second scope\n";

    {
        std::cout << "Using EntityPtr\n";
        String myName("Matias");
        EntityPtr myEntityPtr(&myName);
        myEntityPtr.PrintName();
        
    }
    std::cout << "Out of third scope\n";
    
    {
        std::cout << "Using EntityMov\n";
        EntityMov myEntityMov("Matias");
        myEntityMov.PrintName();
    }
    std::cout << "Out of fourth scope\n";
    std::cin.get();
}

/* Move semantics eliminate the need of using References or Pointers to transfer data without copying it. */

/*
    ============================
    Entity Ownership Semantics
    ============================

    This example demonstrates different ways to pass and manage a `String` object 
    through various `Entity` classes using:

    1. Copy semantics (`EntityCopy`)
    2. Const reference (`EntityRef`)
    3. Raw pointer (`EntityPtr`)
    4. Move semantics (`EntityMov`)

    ------------------------------------------
    1. EntityCopy (Value Semantics, Copy)
    ------------------------------------------
    EntityCopy stores a full copy of the `String` object. 
    This invokes the copy constructor of `String`, duplicating memory.
    
    Use this when:
    - You want value independence.
    - The object is cheap to copy or immutability is required.

    ------------------------------------------
    2. EntityRef (Reference Semantics, Read-Only)
    ------------------------------------------
    EntityRef stores a `const String&` reference.
    It does not copy the data but binds to an existing `String` object.

    Note:
    - You CANNOT pass temporaries (e.g., `"Matias"`) directly to `EntityRef`, 
      because temporaries can't bind to non-persistent references.
    - This is safe for read-only access to existing objects.
    - Unsafe if the refered object is deleted or goes out of scope, as there is no copy/cloning.

    ------------------------------------------
    3. EntityPtr (Pointer Semantics)
    ------------------------------------------
    EntityPtr stores a raw pointer (`String*`) to an external `String` object.

    This is similar to reference semantics, but:
    - Can optionally be null.
    - Offers explicit control over object lifetime.
    - Can be reassigned later.
    - Unsafe if the pointed object is deleted or goes out of scope, as there is no copy/cloning.

    ------------------------------------------
    4. EntityMov (Move Semantics)
    ------------------------------------------
    EntityMov takes ownership of a `String` using move semantics.
    When a temporary or `std::move`-qualified object is passed, 
    the move constructor transfers resources instead of copying them.

    Benefits:
    - No deep copy.
    - Ownership of dynamically allocated memory is transferred.
    - The original object is left in a valid but empty state.

    ------------------------
    Why Use Move Semantics?
    ------------------------
    Move semantics avoid unnecessary copying of expensive resources 
    like heap memory. They are ideal for working with temporaries 
    or when transferring ownership from one object to another.
    No need of references/pointers which make the code error prone, and no need for copying.

    Summary:
    - Use `EntityCopy` for value ownership.
    - Use `EntityRef` for efficient, read-only access.
    - Use `EntityPtr` for optional/nullable ownership with control.
    - Use `EntityMov` for efficient transfer of ownership.

*/