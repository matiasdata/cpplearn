#include <iostream>
#include <string>


class Base
{
public:
    Base(){print();} // BAD: virtual call in constructor
    virtual void print() const {std::cout << "Base\n";}
    virtual ~Base(){print();} // BAD: virtual call in destructor

};

class Derived : public Base
{
public: 
    Derived(){};
    void print() const override { std::cout << "Derived\n";}
};

class TransactionUnsafe
{
public:
    TransactionUnsafe()
    {
        // do some work
        std::cout << "Calling Transaction constructor\n";
        init();
    }
    void init()
    {
        // some extra common work among different constructors, to avoid code repetition
        logTransaction();
    }
    virtual void logTransaction() const = 0;
    ~TransactionUnsafe()
    {
        std::cout << "Calling Transaction destructor\n";
    }
};


class BuyTransactionUnsafe : public TransactionUnsafe
{
public:
    BuyTransactionUnsafe()
    {
        std::cout << "Calling BuyTransaction constructor\n";
    }
    virtual void logTransaction() const
    {
        std::cout << "Buy Transaction logged.\n";
    }
    ~BuyTransactionUnsafe()
    {
        std::cout << "Calling BuyTransaction destructor\n";
    }
};

class SellTransactionUnsafe : public TransactionUnsafe
{
public:
    SellTransactionUnsafe()
    {
        std::cout << "Calling SellTransaction constructor\n";
    }
    virtual void logTransaction() const
    {
        std::cout << "Sell Transaction logged.\n";
    }
    ~SellTransactionUnsafe()
    {
        std::cout << "Calling SellTransaction destructor\n";
    }
};

class Transaction
{
public:
    explicit Transaction(const std::string& logInfo)
    {
        // do some work
        std::cout << "Calling Transaction constructor\n";
        init(logInfo);
    }
    void init(const std::string& logInfo)
    {
        // some extra common work among different constructors, to avoid code repetition
        logTransaction(logInfo);
    }
    void logTransaction(const std::string& logInfo) const
    {
        std::cout << logInfo << "\n";
    }
    ~Transaction()
    {
        std::cout << "Calling Transaction destructor\n";
    }
};


class BuyTransaction : public Transaction
{
public:
    BuyTransaction() : Transaction{createLogString()}
    {
        std::cout << "Calling BuyTransaction constructor\n";
    }
    ~BuyTransaction()
    {
        std::cout << "Calling BuyTransaction destructor\n";
    }
private:
    static std::string createLogString()
    {
        std::string log("Logging Buy Transaction");
        return log;
    }
};

class SellTransaction : public Transaction
{
public:
    SellTransaction() : Transaction{createLogString()}
    {
        std::cout << "Calling SellTransaction constructor\n";
    }
    ~SellTransaction()
    {
        std::cout << "Calling SellTransaction destructor\n";
    }
private:
    static std::string createLogString()
    {
        std::string log("Logging Sell Transaction");
        return log;
    }
};


int main()
{


    Derived d; // expected "Derived" to be printed at ctor and dtor call, but instead "Base" was printed.
    // unexpected behavior due to virtual function call during ctor/dtor call.

    //BuyTransactionUnsafe b; // error due to call to pure virtual logTransaction();
    //SellTransactionUnsafe s;

    BuyTransaction b;
    SellTransaction s;

}

/* 
If we call logTransaction() directly from the Transaction constructor the compiler will issue a warning
but it will still compile. When constructing a BuyTransaction, the ctor will first call the Transaction ctor
and this will call logTransaction() of the base class Transaction which will create an error and abort. Notice
that if we have defined logTransaction() (i.e. not pure virtual) the code will run without problem but calling the 
base logTransaction(), which is usually not what it is expected.
During the base class ctor of a derived class object, the object type is that of the base class. This is because
all derived data member has not been initialized, it will be a gateway to undefined behavior.

The same reasoning applies to the destructor, but the order is reversed, first the derived class dtor is 
called, then the base class dtor is called, once all derived data members are already deleted there is no 
other way to behave than a base class object.

Warnings can disappear if the virtual call is embedded within a non-virtual function, that calls a virtual function
as in the Template method (template method defines skeleton of the algorithm, defering some steps to derived subclasses).
If we put the logTransaction() call inside init() (not virtual), the compiler will not issue a warning.
 
warning: call to pure virtual member function 'logTransaction' has undefined behavior; overrides of 'logTransaction'
in subclasses are not available in the constructor of 'Transaction'

Solution:

One solution is to pass all the required information to the base class constructor, and make logTransaction() no longer
virtual.  That function (base ctor) can then safely call the non-virtual logTransaction.

Notice the use of a static helper function called createLogString() which takes care of creating the log that will be passed
to the base constructor. createLogString must be static because it's called before the BuyTransaction object is constructed.
The function createLogString() is called during base class construction (i.e., before the body of BuyTransaction runs).
But at that point the full BuyTransaction object has not been constructed yet. So you cannot access any non-static members
or call any non-static member functions, because this is not valid yet. A non-static member function needs a valid this pointer
and this isn't fully constructed yet during base class initialization.
A static member function:
    * Does not depend on an instance (this pointer).
    * Can be called on the class itself: BuyTransaction::createLogString().
    * Is guaranteed to be safe to call before the object is constructed.
Instead of relying on internal member variables (which aren’t initialized yet), it receives everything it needs via parameters.

This design helps avoid issues like virtual dispatch in constructors (which is undefined behavior in C++ if not handled carefully).

Key Takeaway:
    * Don’t call virtual functions during construction or destruction, 
    because such calls will never go to a more derived class than that of
    the currently executing constructor or destructor.
*/