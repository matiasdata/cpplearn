#pragma once
#include "datefwd.h"
#include "personimplfwd.h"
#include <string>
#include <memory>

class Person
{
public:
    Person(const std::string& name, const Date& birthday);
    ~Person();

    friend std::ostream& operator<<(std::ostream& os, const Person& thisPerson);

private:
    std::shared_ptr<PersonImpl> pImpl;
};

std::ostream& operator<<(std::ostream& os, const Person& person);