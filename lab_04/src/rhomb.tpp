#pragma once

#include "rhomb.hpp"

#include <cmath>
#include <limits>

template <Scalar T>
Rhomb<T>::Rhomb()
{
    for (auto &point : points_)
    {
        point = std::make_unique<Point<T>>();
    }
}

template <Scalar T>
Rhomb<T>::Rhomb(const std::array<Point<T>, 4> &points)
{
    for (size_t i = 0; i < 4; ++i)
    {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
    validateFigure();
}

template <Scalar T>
Rhomb<T>::Rhomb(const Rhomb<T> &other)
{
    for (size_t i = 0; i < 4; ++i)
    {
        points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
}

template <Scalar T>
Rhomb<T>::Rhomb(Rhomb<T> &&other) noexcept : points_(std::move(other.points_)) {}

template <Scalar T>
Rhomb<T> &Rhomb<T>::operator=(const Rhomb<T> &other)
{
    for (size_t i = 0; i < 4; ++i)
    {
        points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }

    return *this;
}

template <Scalar T>
Rhomb<T> &Rhomb<T>::operator=(Rhomb<T> &&other) noexcept
{
    if (this != &other)
    {
        points_ = std::move(other.points_);
    }

    return *this;
}

template <Scalar T>
bool Rhomb<T>::operator==(const Rhomb<T> &other) const
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (*points_[i] != *other.points_[i])
        {
            return false;
        }
    }
    return true;
}

template <Scalar T>
Rhomb<T>::operator double() const
{
    return area();
}

template <Scalar T>
Point<T> Rhomb<T>::center() const
{
    double centerX = (points_[0]->x() + points_[2]->x()) / 2.0;
    double centerY = (points_[0]->y() + points_[2]->y()) / 2.0;

    return Point<T>(centerX, centerY);
}

template <Scalar T>
void Rhomb<T>::print(std::ostream &os) const
{
    os << "Rhomb points: " << std::endl;
    for (const auto &point : points_)
    {
        os << *point << std::endl;
    }
}

template <Scalar T>
void Rhomb<T>::read(std::istream &is)
{
    for (auto &point : points_)
    {
        std::cout << "Enter point (x y): ";
        is >> *point;
    }

    if (validateFigure())
    {
        std::cout << "The rhomb is valid." << std::endl;
    }
}

template <Scalar T>
bool Rhomb<T>::validateFigure()
{
    auto distance = [](const std::unique_ptr<Point<T>> &p1, const std::unique_ptr<Point<T>> &p2)
    {
        double dx = p2->x() - p1->x();
        double dy = p2->y() - p1->y();
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

    auto slope = [](const std::unique_ptr<Point<T>> &p1, const std::unique_ptr<Point<T>> &p2)
    {
        double dx = p2->x() - p1->x();
        double dy = p2->y() - p1->y();

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

template <Scalar T>
double Rhomb<T>::area() const
{
    auto distance = [](const std::unique_ptr<Point<T>> &p1, const std::unique_ptr<Point<T>> &p2)
    {
        double dx = p2->x() - p1->x();
        double dy = p2->y() - p1->y();
        return std::sqrt(dx * dx + dy * dy);
    };

    double d1 = distance(points_[0], points_[2]);
    double d2 = distance(points_[1], points_[3]);

    return (d1 * d2) / 2.0;
}
