#ifndef DIVIDE
#define DIVIDE
#include "operation.h"

class Divide : public Operation
{
public:
    virtual ~Divide() {}
    virtual double execute(const double & left, const double & right) override { return left / right; }
};

#endif // DIVIDE
