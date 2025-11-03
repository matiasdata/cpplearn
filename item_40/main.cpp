#include <iostream>
#include <string>

class DatabaseID
{
public:
    explicit DatabaseID(int id_) : id{id_} {}
    int getId() {return id;}
private:
    int id;
};

class IPerson
{
public:
    virtual ~IPerson() = default;
    virtual std::string name() const = 0;
    virtual std::string birthDate() const = 0;
};

class PersonInfo
{
public:
    explicit PersonInfo(DatabaseID pid_) : pid{pid_} {}
    virtual ~PersonInfo() = default;
    virtual const char* theName() const {return "Joe Doe";}
    virtual const char* theBirthDate() const {return "01-01-1900";}
private:
    virtual const char* valueDelimOpen() const {return "[";}
    virtual const char* valueDelimClose() const {return "]";}
    DatabaseID pid;
};

class CPerson: public IPerson, private PersonInfo
{
public:
    explicit CPerson(DatabaseID pid_) : PersonInfo{pid_} {} 
    std::string name() const override {return PersonInfo::theName();}
    std::string birthDate() const override {return PersonInfo::theBirthDate();}
private:
    const char* valueDelimOpen() const override {return "";}
    const char* valueDelimClose() const override {return "";}
};



int main() {
    DatabaseID id(1001);
    IPerson* person = new CPerson(id);

    std::cout << "Name: " << person->name() << std::endl;
    std::cout << "Birth Date: " << person->birthDate() << std::endl;

    delete person;
    return 0;
}   

/* 

Summary:
---------
Multiple inheritance (MI) lets a class inherit from more than one base class, 
but it introduces complexity:

1. **Ambiguity in inherited members**: 
   - If two base classes provide a function with the same name, calls can become ambiguous.
   - You must disambiguate with explicit qualification like `Base1::func()`.

2. **The "diamond problem"**:
   - When a shared base class appears through multiple inheritance paths, you may inherit 
     multiple copies of its data. 
   - Use **virtual inheritance** to avoid this and share only *one* instance of the base.
   - Virtual inheritance, however, increases memory footprint and makes construction more complex.

3. **Public vs Private Inheritance in MI**:
   - Public inheritance expresses "is-a": clients can use the derived class where the base is expected.
   - Private inheritance expresses "is-implemented-in-terms-of": implementation reuse, but 
     no "is-a" relationship.

4. **Using MI appropriately**:
   - A common and valid use case for MI: 
       *Publicly inherit from an interface class*, and 
       *privately inherit from a helper class* that provides implementation details.
   - Example: Inheriting publicly from an `IPerson` interface and privately from `PersonInfo`, 
     while overriding virtual methods to adapt old behavior.

Takeaway:
---------
- Favor **single inheritance** when possible — MI makes code harder to understand.
- Use **virtual inheritance** only when necessary to resolve duplication in inheritance hierarchies.
- Apply MI **judiciously**: One base for interface (public), another for implementation help (private).
*/