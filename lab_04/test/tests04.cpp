#include <gtest/gtest.h>
#include "array.hpp"
#include "rectangle.hpp"
#include "rhomb.hpp"
#include "trapezoid.hpp"
#include "point.hpp"

// Test the push_back and size methods of FigureVector
TEST(FigureVectorTest, PushBackAndSize)
{
    Array<std::shared_ptr<Figure<float>>> figures;
    ASSERT_EQ(figures.size(), 0);

    auto rectPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                  Point<float>(0, 2),
                                                  Point<float>(3, 2),
                                                  Point<float>(3, 0)};
    auto rhombPoints = std::array<Point<float>, 4>{Point<float>(0, 1),
                                                   Point<float>(1, 2),
                                                   Point<float>(2, 1),
                                                   Point<float>(1, 0)};
    auto trapezoidPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                       Point<float>(2, 2),
                                                       Point<float>(5, 2),
                                                       Point<float>(7, 0)};

    auto rect = std::make_shared<Rectangle<float>>(rectPoints);
    auto rhomb = std::make_shared<Rhomb<float>>(rhombPoints);
    auto trapezoid = std::make_shared<Trapezoid<float>>(trapezoidPoints);

    figures.push_back(rect);
    EXPECT_EQ(figures.size(), 1);

    figures.push_back(rhomb);
    EXPECT_EQ(figures.size(), 2);

    figures.push_back(trapezoid);
    EXPECT_EQ(figures.size(), 3);
}

// Test the operator[] of FigureVector
TEST(FigureVectorTest, OperatorAccess)
{
    Array<std::shared_ptr<Figure<float>>> figures;

    auto rectPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                  Point<float>(0, 2),
                                                  Point<float>(3, 2),
                                                  Point<float>(3, 0)};
    auto rhombPoints = std::array<Point<float>, 4>{Point<float>(0, 1),
                                                   Point<float>(1, 2),
                                                   Point<float>(2, 1),
                                                   Point<float>(1, 0)};
    auto trapezoidPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                       Point<float>(2, 2),
                                                       Point<float>(5, 2),
                                                       Point<float>(7, 0)};

    auto rect = std::make_shared<Rectangle<float>>(rectPoints);
    auto rhomb = std::make_shared<Rhomb<float>>(rhombPoints);
    auto trapezoid = std::make_shared<Trapezoid<float>>(trapezoidPoints);
    figures.push_back(rect);
    figures.push_back(rhomb);
    figures.push_back(trapezoid);

    EXPECT_EQ(&figures[0], rect);
    EXPECT_EQ(&figures[1], rhomb);
    EXPECT_EQ(&figures[2], trapezoid);
}

// Test the operator double() conversion of FigureVector
TEST(FigureVectorTest, OperatorDouble)
{
    Array<std::shared_ptr<Figure<float>>> figures;

    auto rectPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                  Point<float>(0, 2),
                                                  Point<float>(3, 2),
                                                  Point<float>(3, 0)};
    auto rhombPoints = std::array<Point<float>, 4>{Point<float>(0, 1),
                                                   Point<float>(1, 2),
                                                   Point<float>(2, 1),
                                                   Point<float>(1, 0)};
    auto trapezoidPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                       Point<float>(2, 2),
                                                       Point<float>(5, 2),
                                                       Point<float>(7, 0)};

    auto rect = std::make_shared<Rectangle<float>>(rectPoints);           // Area = 6
    auto rhomb = std::make_shared<Rhomb<float>>(rhombPoints);             // Area = 2
    auto trapezoid = std::make_shared<Trapezoid<float>>(trapezoidPoints); // Area = 10

    figures.push_back(rect);
    figures.push_back(rhomb);
    figures.push_back(trapezoid);

    double expectedTotalArea = 6.0 + 2.0 + 10.0; // Sum of the areas

    double totalArea = static_cast<double>(figures);
    EXPECT_DOUBLE_EQ(totalArea, expectedTotalArea);
}

// Test the erase method of FigureVector
TEST(FigureVectorTest, EraseMethod)
{
    Array<std::shared_ptr<Figure<float>>> figures;

    auto rectPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                  Point<float>(0, 2),
                                                  Point<float>(3, 2),
                                                  Point<float>(3, 0)};
    auto rhombPoints = std::array<Point<float>, 4>{Point<float>(0, 1),
                                                   Point<float>(1, 2),
                                                   Point<float>(2, 1),
                                                   Point<float>(1, 0)};
    auto trapezoidPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                       Point<float>(2, 2),
                                                       Point<float>(5, 2),
                                                       Point<float>(7, 0)};

    auto rect = std::make_shared<Rectangle<float>>(rectPoints);
    auto rhomb = std::make_shared<Rhomb<float>>(rhombPoints);
    auto trapezoid = std::make_shared<Trapezoid<float>>(trapezoidPoints);

    figures.push_back(rect);
    figures.push_back(rhomb);
    figures.push_back(trapezoid);

    EXPECT_EQ(figures.size(), 3);

    figures.erase(1);

    EXPECT_EQ(figures.size(), 2);
    EXPECT_EQ(&figures[1], trapezoid);
}

// Test the center method of Rectangle
TEST(RectangleTest, CenterMethod)
{
    auto rectPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                  Point<float>(0, 2),
                                                  Point<float>(3, 2),
                                                  Point<float>(3, 0)};

    auto rect = Rectangle<float>(rectPoints);

    auto center = rect.center();

    EXPECT_DOUBLE_EQ(center.x(), 1.5);
    EXPECT_DOUBLE_EQ(center.y(), 1.0);
}

// Test the equality operator of Rectangle
TEST(RectangleTest, EqualityOperator)
{
    auto rectPoints1 = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                   Point<float>(0, 2),
                                                   Point<float>(3, 2),
                                                   Point<float>(3, 0)};
    auto rectPoints2 = rectPoints1;

    Rectangle<float> rect1(rectPoints1);
    Rectangle<float> rect2(rectPoints2);

    EXPECT_TRUE(rect1 == rect2);
}

// Test the center method of Romph
TEST(RhombTest, CenterMethod)
{
    auto rhombPoints = std::array<Point<float>, 4>{Point<float>(0, 1),
                                                   Point<float>(1, 2),
                                                   Point<float>(2, 1),
                                                   Point<float>(1, 0)};

    Rhomb<float> rhomb(rhombPoints);

    auto center = rhomb.center();

    EXPECT_DOUBLE_EQ(center.x(), 1.0);
    EXPECT_DOUBLE_EQ(center.y(), 1.0);
}

// Test the equality operator of Rhomb
TEST(RhombTest, EqualityOperator)
{
    auto rhombPoints1 = std::array<Point<float>, 4>{Point<float>(0, 1),
                                                    Point<float>(1, 2),
                                                    Point<float>(2, 1),
                                                    Point<float>(1, 0)};
    auto rhombPoints2 = rhombPoints1;

    Rhomb<float> rhomb1(rhombPoints1);
    Rhomb<float> rhomb2(rhombPoints2);

    EXPECT_TRUE(rhomb1 == rhomb2);
}

// Test the center method of Trapezoid
TEST(TrapezoidTest, CenterMethod)
{
    auto trapezoidPoints = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                       Point<float>(2, 2),
                                                       Point<float>(5, 2),
                                                       Point<float>(7, 0)};

    Trapezoid<float> trapezoid(trapezoidPoints);

    auto center = trapezoid.center();

    EXPECT_DOUBLE_EQ(center.x(), 3.5);
    EXPECT_DOUBLE_EQ(center.y(), 1.0);
}

// Test the equality operator of Trapezoid
TEST(TrapezoidleTest, EqualityOperator)
{
    auto trapezoidPoints1 = std::array<Point<float>, 4>{Point<float>(0, 0),
                                                        Point<float>(2, 2),
                                                        Point<float>(5, 2),
                                                        Point<float>(7, 0)};
    auto trapezoidPoints2 = trapezoidPoints1;

    Trapezoid<float> trapezoid1(trapezoidPoints1);
    Trapezoid<float> trapezoid2(trapezoidPoints2);

    EXPECT_TRUE(trapezoid1 == trapezoid2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}