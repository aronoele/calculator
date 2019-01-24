#include <iostream>
#include <sstream>
#include <limits>
#include "calculator.h"

Calculator::Calculator()
    : mLeft(0)
    , mRight(0)
    , mResult()
{
}

Calculator::~Calculator()
{
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

double Calculator::calculate(const std::string & evaluation)
{
    const int cMAX_OPERANDS_AMOUNT = 2;
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
            // function is too long
            if (elem == "+")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != cMAX_OPERANDS_AMOUNT)
                {
                    clear();
                    throw InputException();
                }
                setOperands();
                auto result = mLeft + mRight;
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
            else if (elem == "-")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != cMAX_OPERANDS_AMOUNT)
                {
                    clear();
                    throw InputException();
                }
                setOperands();
                auto result = mLeft - mRight;
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
            else if (elem == "*")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != cMAX_OPERANDS_AMOUNT)
                {
                    clear();
                    throw InputException();
                }
                setOperands();
                auto result = mLeft * mRight;
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
            else if (elem == "/")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != cMAX_OPERANDS_AMOUNT)
                {
                    clear();
                    throw InputException();
                }
                setOperands();
                if (!isZero(mRight))
                {
                    auto result = mLeft / mRight;
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
                else
                {
                    clear();
                    throw DivideByZeroException();
                }
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

    if (mResult.size() != cMIN_OPERANDS_AMOUNT)
    {
        clear();
        throw InputException();
    }
    auto res = mResult.top();
    clear();
    return res;
}
