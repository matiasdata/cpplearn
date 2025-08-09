#include <iostream>
#include <string>

void logCall(const std::string& str)  // make a log entry
{
    std::cout << str << "\n";
}

class Customer
{
public:
    Customer(){logCall("Customer default constructor");}
    Customer(std::string name_, int age_) : name{name_}, age{age_} {logCall("Customer constructor");}
    Customer(const Customer& other) : name{other.name}, age{other.age} {logCall("Customer copy constructor");} // easy to forget to add age{other.age}
    Customer& operator=(const Customer& other)
    {
        name = other.name;
        age = other.age; // easy to forget this when age was added on a later stage.s
        logCall("Customer copy assigment operator");
        return *this;
    }
    virtual void print() const
    {
        std::cout << "name: " <<  name << " , age: " << age << "\n";
    }
private:
    std::string name{"Not Assigned"};
    int age{0};
};

class PriorityCustomer : public Customer
{
public:
    PriorityCustomer(std::string name_, int age_, int priority_) : Customer(name_,age_), priority{priority_} {}
    PriorityCustomer(const PriorityCustomer& other) : Customer(other), priority{other.priority} {} // easy to forget Customer(other)
    PriorityCustomer& operator=(const PriorityCustomer& other)
    {
        Customer::operator=(other); // easy to forget this line.
        priority = other.priority;
        return *this;
    }

    virtual void print() const override
    {
        Customer::print(); // need to call the print from the base class, equivalent to the line below. 
        //this->Customer::print();
        std::cout << "priority: " << priority << "\n";
    }
private:
    int priority{0};
};

// if you add some extra member data to the class, you need to remember to copy that data on the copy constructor
// and copy assignment. The compiler will not issue any warning if you forget to copy these, and the data will be 
// initialized as specified in the default constructor or default values.

int main()
{
    PriorityCustomer c1("Matias",34,10);
    c1.print();
    PriorityCustomer c2("Juliana", 41,9);
    c2.print();
    PriorityCustomer c3(c1);
    c3.print();
    c3 = c2;
    c3.print();
}

/*

Key takeaways:
    * Copying functions should be sure to copy all of an object’s data
    members and all of its base class parts.
    * Don’t try to implement one of the copying functions in terms of the
    other. Instead, put common functionality in a third function that
    both call.

*/