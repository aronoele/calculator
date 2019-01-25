#ifndef OPERATION
#define OPERATION

class Operation
{
public:
    virtual ~Operation() {}
    virtual double execute(const double & left, const double & right) = 0;
};

#endif // OPERATION

// pure virtual destructor
