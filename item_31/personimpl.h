#pragma once
#include <string>
#include "date.h" // need complete date information as Date is a member

class PersonImpl
{
public:
    PersonImpl(const std::string& name_, const Date& birthday_);

    std::string info() const;
    friend std::ostream& operator<<(std::ostream& os, const PersonImpl& thisPerson);
    
private:
    std::string name;
    Date birthday;
};