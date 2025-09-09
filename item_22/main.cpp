#include <iostream>

class SpeedDataCollectionBad
{
public:
    std::vector<double> speeds; // public: anyone can modify it directly!
};

class SpeedDataCollection
{
public:
    void addValue(double speed)
    {
        if (speed < 0) return;
        total += speed;
        ++count;
    }
    double averageSoFar() const
    {
        return total/count;
    }
private:
    double total{0.0};
    int count{0};
};

// alternative implementation, can be changed without any problems to the user
// makes addValue more expensive but averageSoFar less expensive (tradeoff, depends on 
// user needs, if frequent addValue and infrequent averageSoFar first option is best).

// class SpeedDataCollection
// {
// public:
//     void addValue(double speed)
//     {
//         if (speed < 0) return;
//         average = count * average + speed / (count + 1);
//         ++count;
//     }
//     double averageSoFar() const
//     {
//         return average;
//     }
// private:
//     int count{0};
//     double average{0.0};
// };


int main() {
    SpeedDataCollectionBad s;
    s.speeds.push_back(100);  // client can directly change internal state
    s.speeds.clear();         // client wipes all data accidentally

    SpeedDataCollection sdc;
    sdc.addValue(10);
    sdc.addValue(20);
    std::cout << "average = " << sdc.averageSoFar() << "\n";
}

/*
Key Takeaways:
    * Declare data members private. It gives clients syntactically uniform
    access to data, affords fine-grained access control, allows invariants
    to be enforced, and offers class authors implementation flexibility.
    * protected is no more encapsulated than public.
*/