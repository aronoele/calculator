#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <vector>
#include <stack>

class Calculator
{
public:
    Calculator();
    virtual ~Calculator();
    double calculate (const std::string & evaluation);
private:
    double             mLeft;
    double             mRight;
    std::stack<double> mResult;
    std::vector<std::string> split(const std::string & evaluation, const char separator = ' ');
    bool isNum(const std::string & str);
    void clear();
    void setOperands();
    bool isOutOfRange(const double & value);
    bool isZero(const double & value);
    //double plus();
    //double minus();
    //double multiple();
    //double devide();
};

#endif // CALCULATOR_H

