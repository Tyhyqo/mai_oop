#pragma once

#include "trapezoid.hpp"

#include <cmath>
#include <limits>

template <Scalar T>
Trapezoid<T>::Trapezoid()
{
    for (auto &point : points_)
    {
        point = std::make_unique<Point<T>>();
    }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const std::array<Point<T>, 4> &points)
{
    for (size_t i = 0; i < 4; ++i)
    {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
    validateFigure();
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid<T> &other)
{
    for (size_t i = 0; i < 4; ++i)
    {
        points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(Trapezoid<T> &&other) noexcept : points_(std::move(other.points_)) {}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(const Trapezoid<T> &other)
{
    if (this != &other)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        }
    }

    return *this;
}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(Trapezoid<T> &&other) noexcept
{
    if (this != &other)
    {
        points_ = std::move(other.points_);
    }

    return *this;
}

template <Scalar T>
bool Trapezoid<T>::operator==(const Trapezoid<T> &other) const
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
Trapezoid<T>::operator double() const
{
    return area();
}

template <Scalar T>
Point<T> Trapezoid<T>::center() const {
    double centerX = 0.0;
    double centerY = 0.0;

    for (const auto &point : points_)
    {
        centerX += point->x();
        centerY += point->y();
    }

    centerX /= points_.size();
    centerY /= points_.size();

    return Point<T>(centerX, centerY);
}

template <Scalar T>
void Trapezoid<T>::print(std::ostream &os) const
{
    os << "Trapezoid points: " << std::endl;
    for (const auto &point : points_)
    {
        os << *point << std::endl;
    }
}

template <Scalar T>
void Trapezoid<T>::read(std::istream &is)
{
    for (auto &point : points_)
    {
        std::cout << "Enter point (x y): ";
        is >> *point;
    }

    if (validateFigure())
    {
        std::cout << "The trapezoid is valid." << std::endl;
    }
}

template <Scalar T>
bool Trapezoid<T>::validateFigure()
{

    auto slope = [](const std::unique_ptr<Point<T>> &p1, const std::unique_ptr<Point<T>> &p2) -> double
    {
        double dx = p2->x() - p1->x();
        double dy = p2->y() - p1->y();

        if (std::abs(dx) < 1e-6)
        {
            return std::numeric_limits<double>::infinity();
        }

        return dy / dx;
    };

    double slopeAB = slope(points_[0], points_[1]);
    double slopeCD = slope(points_[2], points_[3]);

    double slopeBC = slope(points_[1], points_[2]);
    double slopeDA = slope(points_[3], points_[0]);

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

template <Scalar T>
double Trapezoid<T>::area() const
{
    double area = 0.0;
    size_t n = points_.size();
    for (size_t i = 0; i < n; ++i)
    {
        size_t j = (i + 1) % n;
        area += (points_[i]->x() * points_[j]->y()) - (points_[j]->x() * points_[i]->y());
    }
    return std::abs(area) / 2.0;
}
