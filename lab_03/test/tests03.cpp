#include <gtest/gtest.h>
#include "figureVector.h"
#include "rectangle.h"
#include "rhomb.h"
#include "trapezoid.h"

// Test the push_back and size methods of FigureVector
TEST(FigureVectorTest, PushBackAndSize)
{
    FigureVector figures;
    ASSERT_EQ(figures.size(), 0);

    auto rectPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                               std::make_pair(0, 2),
                                                               std::make_pair(3, 2),
                                                               std::make_pair(3, 0)};
    auto rhombPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 1),
                                                                std::make_pair(1, 2),
                                                                std::make_pair(2, 1),
                                                                std::make_pair(1, 0)};
    auto trapezoidPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                                    std::make_pair(2, 2),
                                                                    std::make_pair(5, 2),
                                                                    std::make_pair(7, 0)};

    Rectangle *rect = new Rectangle(rectPoints);
    Rhomb *rhomb = new Rhomb(rhombPoints);
    Trapezoid *trapezoid = new Trapezoid(trapezoidPoints);

    figures.push_back(*rect);
    EXPECT_EQ(figures.size(), 1);

    figures.push_back(*rhomb);
    EXPECT_EQ(figures.size(), 2);

    figures.push_back(*trapezoid);
    EXPECT_EQ(figures.size(), 3);
}

// Test the operator[] of FigureVector
TEST(FigureVectorTest, OperatorAccess)
{
    FigureVector figures;

    auto rectPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                               std::make_pair(0, 2),
                                                               std::make_pair(3, 2),
                                                               std::make_pair(3, 0)};
    auto rhombPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 1),
                                                                std::make_pair(1, 2),
                                                                std::make_pair(2, 1),
                                                                std::make_pair(1, 0)};
    auto trapezoidPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                                    std::make_pair(2, 2),
                                                                    std::make_pair(5, 2),
                                                                    std::make_pair(7, 0)};

    Rectangle *rect = new Rectangle(rectPoints);
    Rhomb *rhomb = new Rhomb(rhombPoints);
    Trapezoid *trapezoid = new Trapezoid(trapezoidPoints);

    figures.push_back(*rect);
    figures.push_back(*rhomb);
    figures.push_back(*trapezoid);

    EXPECT_EQ(&figures[0], rect);
    EXPECT_EQ(&figures[1], rhomb);
    EXPECT_EQ(&figures[2], trapezoid);
}

// Test the operator double() conversion of FigureVector
TEST(FigureVectorTest, OperatorDouble)
{
    FigureVector figures;

    auto rectPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                               std::make_pair(0, 2),
                                                               std::make_pair(3, 2),
                                                               std::make_pair(3, 0)};
    auto rhombPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 1),
                                                                std::make_pair(1, 2),
                                                                std::make_pair(2, 1),
                                                                std::make_pair(1, 0)};
    auto trapezoidPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                                    std::make_pair(2, 2),
                                                                    std::make_pair(5, 2),
                                                                    std::make_pair(7, 0)};

    Rectangle *rect = new Rectangle(rectPoints);           // Area = 6
    Rhomb *rhomb = new Rhomb(rhombPoints);                 // Area = 2
    Trapezoid *trapezoid = new Trapezoid(trapezoidPoints); // Area = 10

    figures.push_back(*rect);
    figures.push_back(*rhomb);
    figures.push_back(*trapezoid);

    double expectedTotalArea = 6.0 + 2.0 + 10.0; // Sum of the areas

    double totalArea = static_cast<double>(figures);
    EXPECT_DOUBLE_EQ(totalArea, expectedTotalArea);
}

// Test the erase method of FigureVector
TEST(FigureVectorTest, EraseMethod)
{
    FigureVector figures;

    auto rectPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                               std::make_pair(0, 2),
                                                               std::make_pair(3, 2),
                                                               std::make_pair(3, 0)};
    auto rhombPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 1),
                                                                std::make_pair(1, 2),
                                                                std::make_pair(2, 1),
                                                                std::make_pair(1, 0)};
    auto trapezoidPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                                    std::make_pair(2, 2),
                                                                    std::make_pair(5, 2),
                                                                    std::make_pair(7, 0)};

    Rectangle *rect = new Rectangle(rectPoints);
    Rhomb *rhomb = new Rhomb(rhombPoints);
    Trapezoid *trapezoid = new Trapezoid(trapezoidPoints);

    figures.push_back(*rect);
    figures.push_back(*rhomb);
    figures.push_back(*trapezoid);

    EXPECT_EQ(figures.size(), 3);

    figures.erase(1);

    EXPECT_EQ(figures.size(), 2);
    EXPECT_EQ(&figures[1], trapezoid);
}

// Test the center method of Rectangle
TEST(RectangleTest, CenterMethod)
{
    auto rectPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                               std::make_pair(0, 2),
                                                               std::make_pair(3, 2),
                                                               std::make_pair(3, 0)};

    Rectangle rect(rectPoints);

    auto center = rect.center();

    EXPECT_DOUBLE_EQ(center.first, 1.5);
    EXPECT_DOUBLE_EQ(center.second, 1.0);
}

// Test the equality operator of Rectangle
TEST(RectangleTest, EqualityOperator)
{
    auto rectPoints1 = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                                std::make_pair(0, 2),
                                                                std::make_pair(3, 2),
                                                                std::make_pair(3, 0)};
    auto rectPoints2 = rectPoints1;

    Rectangle rect1(rectPoints1);
    Rectangle rect2(rectPoints2);

    EXPECT_TRUE(rect1 == rect2);
}

// Test the center method of Romph
TEST(RhombTest, CenterMethod)
{
    auto rhombPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 1),
                                                                std::make_pair(1, 2),
                                                                std::make_pair(2, 1),
                                                                std::make_pair(1, 0)};

    Rhomb rhomb(rhombPoints);

    auto center = rhomb.center();

    EXPECT_DOUBLE_EQ(center.first, 1.0);
    EXPECT_DOUBLE_EQ(center.second, 1.0);
}

// Test the equality operator of Rhomb
TEST(RhombTest, EqualityOperator)
{
    auto rhombPoints1 = std::array<std::pair<double, double>, 4>{std::make_pair(0, 1),
                                                                 std::make_pair(1, 2),
                                                                 std::make_pair(2, 1),
                                                                 std::make_pair(1, 0)};
    auto rhombPoints2 = rhombPoints1;

    Rhomb rhomb1(rhombPoints1);
    Rhomb rhomb2(rhombPoints2);

    EXPECT_TRUE(rhomb1 == rhomb2);
}

// Test the center method of Trapezoid
TEST(TrapezoidTest, CenterMethod)
{
    auto trapezoidPoints = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                                    std::make_pair(2, 2),
                                                                    std::make_pair(5, 2),
                                                                    std::make_pair(7, 0)};

    Trapezoid trapezoid(trapezoidPoints);

    auto center = trapezoid.center();

    EXPECT_DOUBLE_EQ(center.first, 3.5);
    EXPECT_DOUBLE_EQ(center.second, 1.0);
}

// Test the equality operator of Trapezoid
TEST(TrapezoidleTest, EqualityOperator)
{
    auto trapezoidPoints1 = std::array<std::pair<double, double>, 4>{std::make_pair(0, 0),
                                                                    std::make_pair(2, 2),
                                                                    std::make_pair(5, 2),
                                                                    std::make_pair(7, 0)};
    auto trapezoidPoints2 = trapezoidPoints1;

    Trapezoid trapezoid1(trapezoidPoints1);
    Trapezoid trapezoid2(trapezoidPoints2);

    EXPECT_TRUE(trapezoid1 == trapezoid2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}