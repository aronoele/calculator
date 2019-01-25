#ifndef MINUS
#define MINUS
#include "operation.h"

class Minus : public Operation
{
public:
    virtual ~Minus() {}
    virtual double execute(const double & left, const double & right) override { return left - right; }
};

#endif // MINUS

