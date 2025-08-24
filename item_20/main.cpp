#include <iostream>
#include <string>

class Person
{
public:
    Person(const std::string& name_, const std::string& address_) : name{name_}, address{address_} 
    {
        std::cout << "[Person Constructor] Creating Person " << name << " living in " << address << "\n";
    }
    Person(const Person& other) : name{other.name}, address{other.address} 
    {
        std::cout << "[Person Copy Constructor] Copying Person " << name << " living in " << address << "\n";
    }
    ~Person()
    {
        std::cout << "[Person Destructor] Destructing Person " << name << " living in " << address << "\n";
    }
    virtual void display() const
    {
        std::cout << "I am " << name << " and I live in " << address << "\n";
    }
private:
    std::string name;
    std::string address;
};

class Student : public Person
{
public:
    Student(const std::string& name_, 
            const std::string& address_, 
            const std::string& schoolName_, 
            const std::string& schoolAddress_) : Person(name_,address_), schoolName{schoolName_}, schoolAddress{schoolAddress_} 
    {
        std::cout << "[Student Constructor] Creating Student of school " << schoolName << " located in " << schoolAddress << "\n";
    }
    Student(const Student& other) : Person(other), schoolName{other.schoolName}, schoolAddress{other.schoolAddress} 
    {
        std::cout << "[Student Copy Constructor] Copying Student of school " << schoolName << " located in " << schoolAddress << "\n";
    }
    ~Student()
    {
        std::cout << "[Student Destructor] Destructing Student of school " << schoolName << " located in " << schoolAddress << "\n";
    }
    friend bool validateStudent(Student s, std::string school);
    friend bool validateStudentConstRef(const Student& s, std::string school);
    virtual void display() const override
    {
        Person::display();
        std::cout << "I study at " << schoolName << " located in " << schoolAddress << "\n";
    }
private:
    std::string schoolName;
    std::string schoolAddress;
};

bool validateStudent(Student s, std::string school) // innapropriate
{
    return s.schoolName == school;
}

bool validateStudentConstRef(const Student& s, std::string school) // appropriate
{
    return s.schoolName == school;
}

// Functions to demonstrate slicing
void printPersonByValue(Person p)
{
    std::cout << "Inside printPersonByValue:\n";
    p.display();
}

void printPersonByConstRef(const Person& p)
{
    std::cout << "Inside printPersonByConstRef:\n";
    p.display();
}

int main()
{
    Student s("Matias","416 Manchester Road", "Imperial College London", "Exhibition Road 1");
    bool b = validateStudent(s,"Imperial College London");
    std::cout << "Student validated: ";
    std::string val = b? "True" : "False";
    std::cout << val << "\n"; 
    bool b2 = validateStudentConstRef(s,"ICL");
    std::cout << "Student validated: ";
    std::string val2 = b2? "True" : "False";
    std::cout << val2 << "\n"; 
    printPersonByValue(s);
    printPersonByConstRef(s);
}