#ifndef MULTIPLY
#define MULTIPLY
#include "operation.h"

class Multiply : public Operation
{
public:
    virtual ~Multiply() {}
    virtual double execute(const double & left, const double & right) override { return left * right; }
};

#endif // MULTIPLY
