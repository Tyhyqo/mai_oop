#pragma once

#include "rectangle.hpp"

#include <cmath>

template <Scalar T>
Rectangle<T>::Rectangle()
{
    for (auto &point : points_)
    {
        point = std::make_unique<Point<T>>();
    }
}

template <Scalar T>
Rectangle<T>::Rectangle(const std::array<Point<T>, 4> &points)
{
    for (size_t i = 0; i < 4; ++i)
    {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
    validateFigure();
}

template <Scalar T>
Rectangle<T>::Rectangle(const Rectangle<T> &other)
{
    for (size_t i = 0; i < 4; ++i)
    {
        points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
}

template <Scalar T>
Rectangle<T>::Rectangle(Rectangle<T> &&other) noexcept : points_(std::move(other.points_)) {}

template <Scalar T>
Rectangle<T> &Rectangle<T>::operator=(const Rectangle<T> &other)
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
Rectangle<T> &Rectangle<T>::operator=(Rectangle<T> &&other) noexcept
{
    if (this != &other)
    {
        points_ = std::move(other.points_);
    }

    return *this;
}

template <Scalar T>
bool Rectangle<T>::operator==(const Rectangle<T> &other) const
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
Rectangle<T>::operator double() const
{
    return area();
}

template <Scalar T>
Point<T> Rectangle<T>::center() const
{
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
void Rectangle<T>::print(std::ostream &os) const
{
    os << "Rectangle points: " << std::endl;
    for (const auto &point : points_)
    {
        os << *point << std::endl;
    }
}

template <Scalar T>
void Rectangle<T>::read(std::istream &is)
{

    for (auto &point : points_)
    {
        std::cout << "Enter point (x y): ";
        is >> *point;
    }

    if (validateFigure())
    {
        std::cout << "The rectangle is valid." << std::endl;
    }
}

template <Scalar T>
bool Rectangle<T>::validateFigure()
{
    double side1 = pow(points_[0]->x() - points_[1]->x(), 2) + pow(points_[0]->y() - points_[1]->y(), 2);
    double side2 = pow(points_[1]->x() - points_[2]->x(), 2) + pow(points_[1]->y() - points_[2]->y(), 2);
    double side3 = pow(points_[2]->x() - points_[3]->x(), 2) + pow(points_[2]->y() - points_[3]->y(), 2);
    double side4 = pow(points_[3]->x() - points_[0]->x(), 2) + pow(points_[3]->y() - points_[0]->y(), 2);

    double diagonal1 = pow(points_[0]->x() - points_[2]->x(), 2) + pow(points_[0]->y() - points_[2]->y(), 2);
    double diagonal2 = pow(points_[1]->x() - points_[3]->x(), 2) + pow(points_[1]->y() - points_[3]->y(), 2);

    if (side1 == side3 && side2 == side4 && diagonal1 == diagonal2)
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("These points do not make up a valid rectangle.");
    }
}

template <Scalar T>
double Rectangle<T>::area() const
{
    double side1 = pow(points_[0]->x() - points_[1]->x(), 2) + pow(points_[0]->y() - points_[1]->y(), 2);
    double side2 = pow(points_[1]->x() - points_[2]->x(), 2) + pow(points_[1]->y() - points_[2]->y(), 2);

    return sqrt(side1 * side2);
}