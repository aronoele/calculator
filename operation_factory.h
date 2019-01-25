#ifndef OPERATION_FACTORY
#define OPERATION_FACTORY
#include <string>
#include "operation.h"

class OperationFactory
{
public:
    ~OperationFactory() {}
    static Operation* getOperation(const std::string & operation);
};

#endif // OPERATION_FACTORY
