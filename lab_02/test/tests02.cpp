#include <gtest/gtest.h>
#include "../include/thirteen.h"

// Default constructor test
TEST(ThirteenTest, DefaultConstructor)
{
    Thirteen num;
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "");
}

// Fill constructor test
TEST(ThirteenTest, ParameterizedConstructor)
{
    Thirteen num(5, 'A');
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "AAAAA");
}

// Fill constructor exception test
TEST(ThirteenTest, ParameterizedConstructorException)
{
    EXPECT_THROW(Thirteen num(5, 'D'), std::invalid_argument);
    
}

// Initializer list constructor test
TEST(ThirteenTest, InitializerListConstructor)
{
    Thirteen num({'1', 'A', '2'});
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "1A2");
}

// Initializer list constructor exception test
TEST(ThirteenTest, InitializerListConstructorException)
{
    EXPECT_THROW(Thirteen num({'0', 'A', '2'}), std::invalid_argument);
}

// Initializer list constructor exception second test
TEST(ThirteenTest, InitializerListConstructorException2)
{
    EXPECT_THROW(Thirteen num({'A', 'D'}), std::invalid_argument);
}

// Copy string constructor test
TEST(ThirteenTest, CopyStringConstructor)
{
    Thirteen num("1A2");
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "1A2");
}

// Copy string constructor exception test
TEST(ThirteenTest, CopyStringConstructorException)
{
    EXPECT_THROW(Thirteen num("0A2"), std::invalid_argument);
}

// Copy string constructor exception second test
TEST(ThirteenTest, CopyStringConstructorException2)
{
    EXPECT_THROW(Thirteen num("AD"), std::invalid_argument);
}

// Copy constructor test
TEST(ThirteenTest, CopyConstructor)
{
    Thirteen num1(5, 'A');
    Thirteen num2(num1);
    std::ostringstream oss;
    num2.print(oss);
    EXPECT_EQ(oss.str(), "AAAAA"); // Ожидаем, что строка будет "AAAAA"
}

// Move constructor test
TEST(ThirteenTest, MoveConstructor)
{
    Thirteen num1(5, 'A');
    Thirteen num2(std::move(num1));
    std::ostringstream oss;
    num2.print(oss);
    EXPECT_EQ(oss.str(), "AAAAA");
}

// Equals method test
TEST(ThirteenTest, EqualsMethod)
{
    Thirteen num1("ABC");
    Thirteen num2("ABC");
    EXPECT_TRUE(num1.equals(num2));
}

// Not equals method test
TEST(ThirteenTest, NotEqualsMethod)
{
    Thirteen num1("ABA");
    Thirteen num2("ABC");
    EXPECT_FALSE(num1.equals(num2));
}

// Greater method test
TEST(ThirteenTest, GreaterMethod)
{
    Thirteen num1("ABC");
    Thirteen num2("ABA");
    EXPECT_TRUE(num1.greater(num2));
}

// Not greater method test
TEST(ThirteenTest, NotGreaterMethod)
{
    Thirteen num1("ABB");
    Thirteen num2("ABC");
    EXPECT_FALSE(num1.greater(num2));
}

// Less method test
TEST(ThirteenTest, LessMethod)
{
    Thirteen num1("ABBA");
    Thirteen num2("ABBB");
    EXPECT_TRUE(num1.less(num2));
}

// Not less method test
TEST(ThirteenTest, NotLessMethod)
{
    Thirteen num1("ABBC");
    Thirteen num2("ABBA");
    EXPECT_FALSE(num1.less(num2));
}

// Add method test
TEST(ThirteenTest, AddMethod)
{
    Thirteen num1("ABC");
    Thirteen num2("ABBA");
    Thirteen num3 = num1.add(num2);
    std::ostringstream oss;
    num3.print(oss);
    EXPECT_EQ(oss.str(), "B9A9");
}

// Subtract method test
TEST(ThirteenTest, SubtractMethod)
{
    Thirteen num1("ACBC");
    Thirteen num2("256");
    Thirteen num3 = num1.sub(num2);
    std::ostringstream oss;
    num3.print(oss);
    EXPECT_EQ(oss.str(), "AA66");
}

// Subtract method exception test
TEST(ThirteenTest, SubtractMethodException)
{
    Thirteen num1("ABCC");
    Thirteen num2("ACBC");
    EXPECT_THROW(num1.sub(num2), std::logic_error);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}