#include <iostream>
#include <sstream>
#include <limits>
#include "calculator.h"

Calculator::Calculator()
    : mLeft(0)
    , mRight(0)
    , mResult()
{
    std::cout << "Minimum value for double: " << std::numeric_limits<double>::min() << std::endl;
    std::cout << "Maximum value for double: " << std::numeric_limits<double>::max() << std::endl;
    std::cout << "Epsilon value for double: " << std::numeric_limits<double>::epsilon() << std::endl;
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
    return (str.find_first_not_of("123456789.") == std::string::npos);
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
         || value < std::numeric_limits<double>::min());
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
            std::cout << "elem: " << elem << std::endl;
            // function is too long
            if (elem == "+")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != 2)
                {
                    clear();
                    return 0;
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
                    return 0;
                }
            }
            else if (elem == "-")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != 2)
                {
                    clear();
                    return 0;
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
                    return 0;
                }
            }
            else if (elem == "*")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != 2)
                {
                    clear();
                    return 0;
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
                    return 0;
                }
            }
            else if (elem == "/")
            {
                std::cout << "size: " << mResult.size() << std::endl;
                if (mResult.size() != 2)
                {
                    clear();
                    return 0;
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
                        return 0;
                    }
                }
                else
                {
                    clear();
                    return 0;
                }
            }
            else if (isNum(elem))
            {
                mResult.push(std::stod(elem));
            }
            else
            {
                clear();
                return 0;
            }
            std::cout << "stack: " << mResult.top() << std::endl;
        }
    }

    double r = (mResult.size() == 1) ? mResult.top() : 0;
    clear();
    return r;
}
