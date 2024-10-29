#include "trapezoid.h"
#include <cmath>
#include <limits>

Trapezoid::Trapezoid() : points_{} {}

Trapezoid::Trapezoid(const std::array<std::pair<double, double>, 4> &points) : points_(points)
{
    validateFigure();
}

Trapezoid::Trapezoid(const Trapezoid &other) : points_(other.points_) {}

Trapezoid::Trapezoid(Trapezoid &&other) noexcept : points_(std::move(other.points_)) {}

Trapezoid &Trapezoid::operator=(const Trapezoid &other)
{
    if (this != &other)
    {
        points_ = other.points_;
    }

    return *this;
}

Trapezoid &Trapezoid::operator=(Trapezoid &&other) noexcept
{
    if (this != &other)
    {
        points_ = std::move(other.points_);
    }

    return *this;
}

bool Trapezoid::operator==(const Trapezoid &other) const
{
    return points_ == other.points_;
}

Trapezoid::operator double() const
{
    return area();
}

std::pair<double, double> Trapezoid::center() const {
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


void Trapezoid::print(std::ostream &os) const
{
    os << "Trapezoid points: " << std::endl;
    for (const auto &point : points_)
    {
        os << "(" << point.first << ", " << point.second << ")" << std::endl;
    }
}

void Trapezoid::read(std::istream &is)
{
    for (auto &point : points_)
    {
        std::cout << "Enter point (x y): ";
        is >> point.first >> point.second;
    }

    if (validateFigure())
    {
        std::cout << "The trapezoid is valid." << std::endl;
    }
}

bool Trapezoid::validateFigure()
{
    const auto &A = points_[0];
    const auto &B = points_[1];
    const auto &C = points_[2];
    const auto &D = points_[3];

    auto slope = [](const std::pair<double, double> &p1, const std::pair<double, double> &p2) -> double
    {
        double dx = p2.first - p1.first;
        double dy = p2.second - p1.second;

        if (std::abs(dx) < 1e-6)
        {
            return std::numeric_limits<double>::infinity();
        }

        return dy / dx;
    };

    double slopeAB = slope(A, B);
    double slopeCD = slope(C, D);

    double slopeBC = slope(B, C);
    double slopeDA = slope(D, A);

    bool isABparallelCD = std::abs(slopeAB - slopeCD) < 1e-6;
    bool isBCparallelDA = std::abs(slopeBC - slopeDA) < 1e-6;

    if (isABparallelCD || isBCparallelDA)
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("These points do not make up a valid trapezoid.");
    }
}

double Trapezoid::area() const
{
    double area = 0.0;
    size_t n = points_.size();
    for (size_t i = 0; i < n; ++i)
    {
        size_t j = (i + 1) % n;
        area += (points_[i].first * points_[j].second) - (points_[j].first * points_[i].second);
    }
    return std::abs(area) / 2.0;
}
