#ifndef PLUS
#define PLUS
#include "operation.h"

class Plus : public Operation
{
public:
    virtual ~Plus() {}
    virtual double execute(const double & left, const double & right) override { return left + right; }
};

#endif // PLUS

