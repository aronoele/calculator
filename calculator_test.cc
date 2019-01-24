#include <iostream>
#include "gtest/gtest.h"
#include "calculator.h"

Calculator calc;

TEST(CalculatorTest, TestOperationSimplePlus1)
{
    auto result = calc.calculate("2 2 +");
    EXPECT_DOUBLE_EQ(4, result);
}

TEST(CalculatorTest, TestOperationSimplePlus2)
{
    auto result = calc.calculate("2.3 2 +");
    EXPECT_DOUBLE_EQ(4.3, result);
}

TEST(CalculatorTest, TestOperationSimplePlus3)
{
    auto result = calc.calculate("2 2.3 +");
    EXPECT_DOUBLE_EQ(4.3, result);
}

TEST(CalculatorTest, TestOperationSimplePlus4)
{
    auto result = calc.calculate("-2 2 +");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestOperationSimpleMinus)
{
    auto result = calc.calculate("5 2 -");
    EXPECT_DOUBLE_EQ(3, result);
}

TEST(CalculatorTest, TestOperationSimpleMultiply)
{
    auto result = calc.calculate("2 3 *");
    EXPECT_DOUBLE_EQ(6, result);
}

TEST(CalculatorTest, TestOperationSimpleDivide)
{
    auto result = calc.calculate("4 2 /");
    EXPECT_DOUBLE_EQ(2, result);
}

TEST(CalculatorTest, TestCalculateLongNotation)
{
    auto result = calc.calculate("5 3 + 7 * 2 /");
    EXPECT_DOUBLE_EQ(28, result);
}

TEST(CalculatorTest, TestCalculateDivideByZero)
{
    try
    {
        auto result = calc.calculate("5 1 - 0 /");
    }
    catch (DivideByZeroException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Divide by zero");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateEmptyString)
{
    auto result = calc.calculate("");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateTwoSpaces)
{
    auto result = calc.calculate("5 1  - 4 /");
    EXPECT_DOUBLE_EQ(1, result);
}

TEST(CalculatorTest, TestCalculateWrongOperands)
{
    try
    {
        auto result = calc.calculate("2 2 + 2 2");
    }
    catch (InputException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Wrong input");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateWrongOperators)
{
    try
    {
        auto result = calc.calculate("2 2 + -");
    }
    catch (InputException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Wrong input");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateWrongArguments)
{
    try
    {
        auto result = calc.calculate("2 a +");
    }
    catch (InputException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Wrong input");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateWrongSymbolsInString)
{
    try
    {
        auto result = calc.calculate("2 3 + qwe");
    }
    catch (InputException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Wrong input");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateRandomString)
{
    try
    {
        auto result = calc.calculate("qwerty");
    }
    catch (InputException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Wrong input");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateOperationsWithDoubles)
{
    try
    {
        auto result = calc.calculate("5 2 /");
    }
    catch (NumericLimitsException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Numeric limit");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithPlus)
{
    try
    {
        auto result = calc.calculate("1.79769e+308 1.79769e+308 +");
    }
    catch (NumericLimitsException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Numeric limit");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithMinus1)
{
    try
    {
        auto result = calc.calculate("-10 1.79769e+308 -");
    }
    catch (NumericLimitsException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Numeric limit");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithMinus2)
{
    try
    {
        auto result = calc.calculate("1.79769e+307 1.79769e+308 -");
    }
    catch (NumericLimitsException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Numeric limit");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithMultiply)
{
    try
    {
        auto result = calc.calculate("1.79769e+308 1.79769e+308 *");
    }
    catch (NumericLimitsException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Numeric limit");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithDivide)
{
    try
    {
        auto result = calc.calculate("1 1.79769e+308 /");
    }
    catch (NumericLimitsException & e)
    {
        EXPECT_EQ(std::string(e.what()), "Numeric limit");
        std::cout << "Exception: " << e.what() << std::endl;
    }
}
