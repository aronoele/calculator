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
    auto result = calc.calculate("5 1 - 0 /");
    EXPECT_DOUBLE_EQ(0, result);
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
    auto result = calc.calculate("2 2 + 2 2");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateWrongOperators)
{
    auto result = calc.calculate("2 2 + -");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateWrongArguments)
{
    auto result = calc.calculate("2 a +");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateWrongSymbolsInString)
{
    auto result = calc.calculate("2 3 + qwe");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateRandomString)
{
    auto result = calc.calculate("qwerty");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateOperationsWithDoubles)
{
    auto result = calc.calculate("5 2 /");
    EXPECT_DOUBLE_EQ(2.5, result);
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithPlus)
{
    auto result = calc.calculate("1.79769e+308 1.79769e+308 +");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithMinus1)
{
    auto result = calc.calculate("-10 1.79769e+308 -");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithMinus2)
{
    auto result = calc.calculate("1.79769e+307 1.79769e+308 -");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithMultiply)
{
    auto result = calc.calculate("1.79769e+308 1.79769e+308 *");
    EXPECT_DOUBLE_EQ(0, result);
}

TEST(CalculatorTest, TestCalculateNumericLimitsWithDivide)
{
    auto result = calc.calculate("1 1.79769e+308 /");
    EXPECT_DOUBLE_EQ(0, result);
}
