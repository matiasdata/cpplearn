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

int main()
{
    std::cout << "=== Composition Example ===\n";
    Widget wc(5);
    wc.startMonitoring();
    std::cout << "\n=== Private Inheritance Example ===\n";
    WidgetPI wpi(5);
    wpi.startMonitoring();
}