#include "personimpl.h"

PersonImpl::PersonImpl(const std::string& name_, 
                       const Date& birthday_) : name{name_}, birthday{birthday_} {}

std::ostream& operator<<(std::ostream& os, const PersonImpl& thisPerson)
{
    return os << thisPerson.name << " was born on " << thisPerson.birthday;
}