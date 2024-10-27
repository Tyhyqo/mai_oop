#include "rhomb.h"
#include <cmath>
#include <limits>

Rhomb::Rhomb() : points_{} {}

Rhomb::Rhomb(const std::array<std::pair<double, double>, 4> &points) : points_(points)
{
    validateFigure();
}

Rhomb::Rhomb(const Rhomb &other) : points_(other.points_) {}

Rhomb::Rhomb(Rhomb &&other) noexcept : points_(std::move(other.points_)) {}

Rhomb &Rhomb::operator=(const Rhomb &other)
{
    if (this != &other)
    {
        points_ = other.points_;
    }

    return *this;
}

Rhomb &Rhomb::operator=(Rhomb &&other) noexcept
{
    if (this != &other)
    {
        points_ = std::move(other.points_);
    }

    return *this;
}

bool Rhomb::operator==(const Rhomb &other) const
{
    return points_ == other.points_;
}

Rhomb::operator double() const
{
    return area();
}

std::pair<double, double> Rhomb::center() const
{
    double centerX = (points_[0].first + points_[2].first) / 2.0;
    double centerY = (points_[0].second + points_[2].second) / 2.0;

    return {centerX, centerY};
}

void Rhomb::print(std::ostream &os) const
{
    os << "Rhomb points: " << std::endl;
    for (const auto &point : points_)
    {
        os << "(" << point.first << ", " << point.second << ")" << std::endl;
    }
}

void Rhomb::read(std::istream &is)
{
    for (auto &point : points_)
    {
        std::cout << "Enter point (x y): ";
        is >> point.first >> point.second;
    }

    if (validateFigure())
    {
        std::cout << "The rhomb is valid." << std::endl;
    }
}

bool Rhomb::validateFigure()
{
    auto distance = [](const std::pair<double, double> &p1, const std::pair<double, double> &p2)
    {
        double dx = p2.first - p1.first;
        double dy = p2.second - p1.second;
        return std::sqrt(dx * dx + dy * dy);
    };

    double sideA = distance(points_[0], points_[1]);
    double sideB = distance(points_[1], points_[2]);
    double sideC = distance(points_[2], points_[3]);
    double sideD = distance(points_[3], points_[0]);

    double epsilon = 1e-6;
    bool sidesEqual = std::abs(sideA - sideB) < epsilon &&
                      std::abs(sideB - sideC) < epsilon &&
                      std::abs(sideC - sideD) < epsilon;

    if (!sidesEqual)
    {
        return false;
    }

    auto slope = [](const std::pair<double, double> &p1, const std::pair<double, double> &p2)
    {
        double dx = p2.first - p1.first;
        double dy = p2.second - p1.second;

        if (std::abs(dx) < 1e-6)
            return std::numeric_limits<double>::infinity();

        return dy / dx;
    };

    double slopeAB = slope(points_[0], points_[1]);
    double slopeBC = slope(points_[1], points_[2]);
    double slopeCD = slope(points_[2], points_[3]);
    double slopeDA = slope(points_[3], points_[0]);

    bool isABparallelCD = std::abs(slopeAB - slopeCD) < epsilon ||
                          (std::isinf(slopeAB) && std::isinf(slopeCD));

    bool isBCparallelDA = std::abs(slopeBC - slopeDA) < epsilon ||
                          (std::isinf(slopeBC) && std::isinf(slopeDA));

    if (isABparallelCD && isBCparallelDA)
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("These points do not make up a valid rhomb.");
    }
}

double Rhomb::area() const
{
    auto distance = [](const std::pair<double, double> &p1, const std::pair<double, double> &p2)
    {
        double dx = p2.first - p1.first;
        double dy = p2.second - p1.second;
        return std::sqrt(dx * dx + dy * dy);
    };

    double d1 = distance(points_[0], points_[2]);
    double d2 = distance(points_[1], points_[3]);

    return (d1 * d2) / 2.0;
}
