#include "rectangle.h"
#include <cmath>

Rectangle::Rectangle() : points_{} {}

Rectangle::Rectangle(const std::array<std::pair<double, double>, 4> &points) : points_(points)
{
    validateFigure();
}

Rectangle::Rectangle(const Rectangle &other) : points_(other.points_) {}

Rectangle::Rectangle(Rectangle &&other) noexcept : points_(std::move(other.points_)) {}

Rectangle &Rectangle::operator=(const Rectangle &other)
{
    if (this != &other)
    {
        points_ = other.points_;
    }

    return *this;
}

Rectangle &Rectangle::operator=(Rectangle &&other) noexcept
{
    if (this != &other)
    {
        points_ = std::move(other.points_);
    }

    return *this;
}

bool Rectangle::operator==(const Rectangle &other) const
{
    return points_ == other.points_;
}

Rectangle::operator double() const
{
    return area();
}

std::pair<double, double> Rectangle::center() const
{
    double centerX = 0.0;
    double centerY = 0.0;

    for (const auto &point : points_)
    {
        centerX += point.first;
        centerY += point.second;
    }

    centerX /= points_.size();
    centerY /= points_.size();

    return {centerX, centerY};
}

void Rectangle::print(std::ostream &os) const
{
    os << "Rectangle points: " << std::endl;
    for (const auto &point : points_)
    {
        os << "(" << point.first << ", " << point.second << ")" << std::endl;
    }
}

void Rectangle::read(std::istream &is)
{

    for (auto &point : points_)
    {
        std::cout << "Enter point (x y): ";
        is >> point.first >> point.second;
    }

    if (validateFigure())
    {
        std::cout << "The rectangle is valid." << std::endl;
    }
}

bool Rectangle::validateFigure()
{
    double side1 = pow(points_[0].first - points_[1].first, 2) + pow(points_[0].second - points_[1].second, 2);
    double side2 = pow(points_[1].first - points_[2].first, 2) + pow(points_[1].second - points_[2].second, 2);
    double side3 = pow(points_[2].first - points_[3].first, 2) + pow(points_[2].second - points_[3].second, 2);
    double side4 = pow(points_[3].first - points_[0].first, 2) + pow(points_[3].second - points_[0].second, 2);

    double diagonal1 = pow(points_[0].first - points_[2].first, 2) + pow(points_[0].second - points_[2].second, 2);
    double diagonal2 = pow(points_[1].first - points_[3].first, 2) + pow(points_[1].second - points_[3].second, 2);

    if (side1 == side3 && side2 == side4 && diagonal1 == diagonal2)
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("These points do not make up a valid rectangle.");
    }
}

double Rectangle::area() const
{
    double side1 = pow(points_[0].first - points_[1].first, 2) + pow(points_[0].second - points_[1].second, 2);
    double side2 = pow(points_[1].first - points_[2].first, 2) + pow(points_[1].second - points_[2].second, 2);

    return sqrt(side1 * side2);
}