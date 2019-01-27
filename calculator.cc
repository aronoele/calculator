#include <iostream>
#include <sstream>
#include <limits>
#include "constants.h"
#include "calculator.h"
#include "operation_factory.h"

Calculator::Calculator()
    : mLeft(0)
    , mRight(0)
    , mResult()
    , mOperation(nullptr)
{
}

Calculator::~Calculator()
{
    if (mOperation)
    {
        delete mOperation;
        mOperation = nullptr;
    }
}

std::vector<std::string> Calculator::split(const std::string & evaluation, const char separator/* = ' '*/)
{
    std::stringstream ss(evaluation);
    std::string item;
    std::vector<std::string> items;

    // not obvious that getline will retrieve elems splitted by separator
    while (std::getline(ss, item, separator))
    {
        if (!item.empty())
        {
            items.push_back(item);
        }
    }
    return items;
}

bool Calculator::isNum(const std::string & str)
{
    // e notation could also be wrong
    return (str.find_first_not_of("0123456789.-+e") == std::string::npos);
}

bool Calculator::isOperation(const std::string & str)
{
    return (str == "+") || (str == "-") || (str == "*") || (str == "/");
}

void Calculator::clear()
{
    while (!mResult.empty())
    {
        mResult.pop();
    }
}

void Calculator::setOperands()
{
    mRight = mResult.top();
    mResult.pop();
    mLeft = mResult.top();
    mResult.pop();
}

bool Calculator::isZero(const double & value)
{
    return (value < std::numeric_limits<double>::epsilon());
}

bool Calculator::isOutOfRange(const double & value)
{
    return (value > std::numeric_limits<double>::max()
         /*|| value < std::numeric_limits<double>::min()*/);
}

void Calculator::performOperation() // TODO: change the name
{
    if (mResult.size() != CalculatorConstants::cMAX_OPERANDS_AMOUNT)
    {
        clear();
        throw InputException();
    }
    setOperands();
    if (mOperation)
    {
        if (/*divide && */isZero(mRight))
        {
            clear();
            throw DivideByZeroException();
        }
        auto result = mOperation->execute(mLeft, mRight);
        delete mOperation;
        mOperation = nullptr;
        if (!isOutOfRange(result))
        {
            mResult.push(result);
        }
        else
        {
            clear();
            throw NumericLimitsException();
        }
    }
}

double Calculator::calculate(const std::string & evaluation)
{
    if (evaluation.empty())
    {
        mResult.push(0);
    }
    else
    {
        auto const splittedEvaluation = split(evaluation);

        for (const auto & elem : splittedEvaluation)
        {
            if (isOperation(elem))
            {
                mOperation = OperationFactory::getOperation(elem);
                performOperation();
            }
            else if (isNum(elem))
            {
                mResult.push(std::stod(elem));
            }
            else
            {
                clear();
                throw InputException();
            }
        }
    }

    double res;
    if (mResult.size() == CalculatorConstants::cMIN_OPERANDS_AMOUNT)
    {
        res = mResult.top();
        clear();
    }
    else
    {
        clear();
        throw InputException();
    }
    return res;
}
