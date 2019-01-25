#include "operation_factory.h"
#include "plus.h"
#include "minus.h"
#include "multiply.h"
#include "divide.h"

Operation* OperationFactory::getOperation(const std::string & operation)
{
    if (operation == "+")
    {
        return new Plus();
    }
    else if (operation == "-")
    {
        return new Minus();
    }
    else if (operation == "*")
    {
        return new Multiply();
    }
    /*else if (operation == "/")*/
    return new Divide();
}
