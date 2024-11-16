#pragma once

#include <concepts>
#include <type_traits>
#include <iostream>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point
{
public:
    Point();
    Point(T x, T y);

    T x() const;
    T y() const;

    void set_x(T x);
    void set_y(T y);

    bool operator==(const Point<T> &other) const;

private:
    T x_{};
    T y_{};
};

template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Point<T> &point)
{
    os << "(" << point.x() << ", " << point.y() << ")";
    return os;
}

template <Scalar T>
inline std::istream &operator>>(std::istream &is, Point<T> &point)
{
    T x, y;
    is >> x >> y;
    point.set_x(x);
    point.set_y(y);
    return is;
}

#include "point.tpp"

