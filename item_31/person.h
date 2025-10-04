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


/*

Person only has a pointer to a PersonImpl, and takes a Date (and an std::string as well) as inputs for the constructor, 
it does not need to have PersonImpl or Date definition, only needs them to be declared. If any of these were actual
data members of the class (not a pointer, as in this pimpl idiom), then we would need their actual definitions in order
to be compiled, because the class needs to know how much memory it needs to allocate.

This gives much more modularity to the class, as does not depend on Date or PersonImpl implementations.
    * If we change date.cpp (implementation), we only need to recompile date.cpp (no need to recompile person).
    * If we change personimpl.cpp (implementation), we only need to recompile personimpl.cpp (no need to recompile person).
This is true if we include declaration or definition headers (datefwd.h or date.h). 

However, if we chance date.h (interface), we need to recompile person.cpp. This is because person.cpp includes date.h.
But this does not cascade to main, whereas if we change date.h and this was included with #include "date.h" then we would
have to recompile main because person.h would be indirectly modified by the modification made to date.h (remember, include
statements are fancy copy pasting the text in place). If you modify date.h, all .cpp files that include person.h indirectly
see the change. Therefore, they all must be recompiled, even though they don’t use anything that changed.

Summary:

| Change                  | With forward declarations (datefwd.h)    | With definition declariations (date.h)                             |
| ----------------------- | ---------------------------------------- | ------------------------------------------------------------------ |
| Modify `date.cpp`       | Recompile `date.cpp` only                | Recompile `date.cpp` only                                          |
| Modify `date.h`         | Recompile `personimpl.cpp`, `person.cpp` | Recompile **everything** that includes `person.h` (main.cpp, etc.) |
| Modify `personimpl.cpp` | Recompile `personimpl.cpp` only          | Same                                                               |
| Modify `personimpl.h`   | Recompile `personimpl.cpp`, `person.cpp` | Recompile **everything** that includes `person.h`                  |

*/