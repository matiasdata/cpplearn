#include <iostream>
#include "virtual.h"
#include "templategc.h"
#include "strategyfungc.h"
#include "strategyclassicgc.h"
#include <memory>

int main()
{
    // Virtual approach
    VirtualApproach::GameCharacter vg(80);
    VirtualApproach::Warrior vw(50);
    std::cout << "GameCharacter vg Health: " << vg.healthValue() << "\n";
    std::cout << "Warrior vw Health: " << vw.healthValue() << "\n";

    //Template approach with Non Virtual Interface (NVI)
    TemplateApproach::GameCharacter g(50);
    TemplateApproach::Warrior w(20);
    std::cout << "GameCharacter g Health: " << g.healthValue() << "\n";
    std::cout << "Warrior w Health: " << w.healthValue() << "\n";


    // Functional Strategy approach
    StratFunApproach::GameCharacter gc1{StratFunApproach::loseHealthFast};
    StratFunApproach::GameCharacter gc2{StratFunApproach::loseHealthSlow()};
    StratFunApproach::GameCharacter gc3{StratFunApproach::loseHealthSuperSlow};
    std::cout << "gc1 Health: " << gc1.healthValue() << "\n";
    std::cout << "gc2 Health: " << gc2.healthValue() << "\n";
    std::cout << "gc2 Health: " << gc3.healthValue() << "\n";

    // Classic Strategy approach
    ClassicStrategyApproach::GameCharacter csgc1(std::make_shared<ClassicStrategyApproach::HealthCalculator>());
    ClassicStrategyApproach::GameCharacter csgc2(std::make_shared<ClassicStrategyApproach::FastDecay>());
    ClassicStrategyApproach::GameCharacter csgc3(std::make_shared<ClassicStrategyApproach::SlowDecay>());
    std::cout << "csgc1 Health: " << csgc1.healthValue() << "\n";
    std::cout << "csgc2 Health: " << csgc2.healthValue() << "\n";
    std::cout << "csgc2 Health: " << csgc3.healthValue() << "\n";
}
 
/*

Summary
The fundamental advice of this Item is to consider alternatives to virtual
functions when searching for a design for the problem you’re trying to solve.
Here’s a quick recap of the alternatives we examined:
    
    * Use the non-virtual interface idiom (NVI idiom), a form of the
    Template Method design pattern that wraps public non-virtual
    member functions around less accessible virtual functions.
    
    * Replace virtual functions with function pointer data members, a
    stripped-down manifestation of the Strategy design pattern.
    
    * Replace virtual functions with std::function data members, thus
    allowing use of any callable entity with a signature compatible with
    what you need. This, too, is a form of the Strategy design pattern.
    
    * Replace virtual functions in one hierarchy with virtual functions
    in another hierarchy. This is the conventional implementation of
    the Strategy design pattern.

This isn’t an exhaustive list of design alternatives to virtual functions,
but it should be enough to convince you that there are alternatives.
Furthermore, their comparative advantages and disadvantages should
make clear that you should consider them.

To avoid getting stuck in the ruts of the road of object-oriented design,
give the wheel a good jerk from time to time. There are lots of other
roads. It’s worth taking the time to investigate them.

Key takeaways:
    * Alternatives to virtual functions include the NVI idiom and various
    forms of the Strategy design pattern. The NVI idiom is itself an example
    of the Template Method design pattern.
    * A disadvantage of moving functionality from a member function to a
    function outside the class is that the non-member function lacks access
    to the class’s non-public members.
    * std::function objects act like generalized function pointers. Such 
    objects support all callable entities compatible with a given target 
    signature.

*/

/*

 Design Characteristics
============================================================================================================================================================
| Approach              | Key Idea                                        | Flexibility  | Encapsulation                  | Overhead  | Style              |
|------------------------|------------------------------------------------|--------------|--------------------------------|-----------|--------------------|
| Basic Virtual Function | Derived classes override virtual members       | Medium       | Good                           | Low       | Classic OOP        |
| NVI (Template Method)  | Public non-virtual calls private virtual "core"| Medium       | Excellent (base controls order)| Low       | Traditional OOP    |
| Functional Strategy    | Pass callable (function, lambda, functor)      | High         | Weaker (external logic)        | Low       | Modern / Functional|
| Classic Strategy       | Encapsulate algorithm in separate hierarchy    | High         | Strong (interface-based)       | Higher    | Pure OOP           |

============================================================================================================================================================

Advantages and Disadvantages
===========================================================================================================================================================
| Approach              | Advantages                                                    | Disadvantages                                                   |
|------------------------|--------------------------------------------------------------|-----------------------------------------------------------------|
| Basic Virtual Function | - Simple and intuitive                                       | - Behavior fixed per class                                      |
|                        | - Full access to base internals                              | - Limited runtime flexibility                                   |
|                        | - Efficient dispatch via vtable                              | - Tight coupling through inheritance                            |

| NVI (Template Method)  | - Base controls when virtuals run                            | - Slightly more boilerplate                                     |
|                        | - Ensures pre/post conditions                                | - Less freedom for derived classes                              |
|                        | - Good for enforcing invariants or logging                   |                                                                 |

| Functional Strategy    | - Per-object customization                                   | - External callables lack private access                        |
| (using std::function)  | - Works with lambdas, functors, bound members                | - Must manually maintain consistency                            |
|                        | - Easy runtime swapping                                      |                                                                 |

| Classic Strategy       | - Decouples behavior from data                               | - More code and indirection                                     |
|                        | - Extensible via new strategy classes                        | - Harder lifetime management                                    |
|                        | - Strong encapsulation                                       | - Slightly higher runtime cost                                  |
===========================================================================================================================================================
*/


/*
On C++ most vexing parse:
In C++ anything that can be parsed as a declaration will be parsed as one. The following:
StratFunApproach::GameCharacter gc2(StratFunApproach::loseHealthSlow());
will be parsed as a function gc2 that returns a GameCharater and takes as input a function (that itself returns a loseHealthSlow object with no parameters).

int f(A()); 
is shorthand for:
int f(A(*)());
That is: f is a function taking a pointer to a function returning an A.
That’s a legacy rule going back to C. You can see the same behavior with 
int x(int());
which is a declaration of a function x that takes a pointer to a function returning int.
*/