#include "person.h"
#include "personimpl.h"

Person::Person(const std::string& name, const Date& birthday) : pImpl{std::make_shared<PersonImpl>(name,birthday)} {}

Person::~Person() = default;  



std::ostream& operator<<(std::ostream& os, const Person& thisPerson)
{
    return operator<<(os, *(thisPerson.pImpl));
}