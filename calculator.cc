#include <iostream>
#include <sstream>
#include <limits>
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
        delete[] mOperation;
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
    std::cout << "size: " << mResult.size() << std::endl;
    const int cMAX_OPERANDS_AMOUNT = 2;
    if (mResult.size() != cMAX_OPERANDS_AMOUNT)
    {
        clear();
        throw InputException();
    }
    setOperands();
    if (mOperation)
    {
        auto result = mOperation->execute(mLeft, mRight);
        //delete[] mOperation;
        //mOperation = nullptr;
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
    const int cMIN_OPERANDS_AMOUNT = 1;
    if (evaluation.empty())
    {
        mResult.push(0);
    }
    else
    {
        auto const splittedEvaluation = split(evaluation);

        for (const auto & elem : splittedEvaluation)
        {
            std::cout << "elem: " << elem << std::endl;

            if (isOperation(elem))
            {
                mOperation = OperationFactory::getOperation(elem);
                try
                {
                    performOperation();
                }
                catch(std::exception & e)
                {
                    throw e;
                }
            }
            else if (isNum(elem))
            {
                mResult.push(std::stod(elem));
                std::cout << "stack: " << mResult.top() << std::endl;
            }
            else
            {
                clear();
                throw InputException();
            }
        }
    }

    double res;
    if (mResult.size() == cMIN_OPERANDS_AMOUNT)
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
