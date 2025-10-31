#include <iostream>
#include <string>

class Timer
{
public:
    explicit Timer(int tickFrequency_) : tickFrequency{tickFrequency_} {}
    virtual void onTick() const {std::cout << "[Timer] tick!\n";}
    void start() const {onTick();}
private:
    int tickFrequency;
};

class Widget
{
private:
    class WidgetTimer; // forward declaration
    WidgetTimer* timer;
public:
    Widget(int tickFrequency_);
    Widget(WidgetTimer* pw) : timer{pw} {};
    void collectStats() const {
        std::cout << "Collecting stats from Widget.\n";
    }
    void startMonitoring() const;
};

class Widget::WidgetTimer : public Timer
{
public:
    WidgetTimer(Widget& widget_, int tickFrequency) : Timer{tickFrequency}, widget{widget_} {}
    void onTick() const override {
        std::cout << "Gathering Widget stats...\n";
        widget.collectStats();
        std::cout << "[WidgetTimer] tick!\n";
    }
private:
    Widget& widget;
};

Widget::Widget(int tickFrequency_) : timer(new WidgetTimer(*this, tickFrequency_)) {}

void Widget::startMonitoring() const  { timer->start(); }


class WidgetPI : private Timer
{
public:
    WidgetPI(int tickFrequency_) : Timer{tickFrequency_} {}
    void startMonitoring() const { start(); }
private:
    void onTick() const override
    {
        std::cout << "Gathering Widget stats...\n";
        collectStats();
        std::cout << "[Widget] tick!\n";
    }
    void collectStats() const {
        std::cout << "Collecting stats from Widget.\n";
    }

};
// With Private inheritance, WidgetPI inherits all members (functions and data) from the base class (Timer),
// but the access level changes: public protected and private members become private, the class itself can
// access all, but users can't access any of the inherited members as these are now private. e.g. a user call:
// wpi.start();
// would be an error (inaccessible).

int main()
{
    std::cout << "=== Composition Example ===\n";
    Widget wc(5);
    wc.startMonitoring();
    std::cout << "\n=== Private Inheritance Example ===\n";
    WidgetPI wpi(5);
    wpi.startMonitoring();
    // wpi.start(); // error, inaccessible.
}

# /*

Use private inheritance judiciously

Behavior

* Private inheritance lets a derived class reuse implementation
  from a base class, but not its interface.
* All public and protected members of the base become private
  within the derived class.
* Implicit conversions from derived to base are disallowed.
* The relationship is *not* “is-a”, but rather
  “is-implemented-in-terms-of”.
* Private inheritance is an implementation detail, not a
  design-level relationship.

Comparison

Public inheritance → “is-a” relationship
• The derived class publicly exposes the base interface.
• Enables implicit upcasting (Derived → Base).
• Used when the derived object should be usable wherever
a base object is expected.

Private inheritance → “is-implemented-in-terms-of” relationship
• Implementation is inherited, but the interface is hidden.
• Base functionality is used internally by the derived class.
• Useful when the derived class must access protected members
or override virtual functions.
• Also allows the Empty Base Optimization (EBO) when the
base has no data.

Composition → “has-a” or “is-built-from” relationship
• The derived class contains a base object as a member.
• Clearer and safer — the preferred mechanism for code reuse.
• Cannot access protected members or override virtuals.
• Slightly more verbose because delegation is explicit.

Guidelines

* Prefer composition for reuse and simplicity.
* Use private inheritance only when:

  1. The derived class must override virtual functions, or
  2. It requires access to base’s protected members, or
  3. EBO is beneficial for space optimization.

Summary:
* Public inheritance = interface reuse (“is-a”)
* Private inheritance = implementation reuse (“is-implemented-in-terms-of”)
* Composition = containment (“has-a”)
=====================================

*/
