#pragma once

#include "point.hpp"

template <Scalar T>
Point<T>::Point() : x_(T()), y_(T()) {}

template <Scalar T>
Point<T>::Point(T x, T y) : x_(x), y_(y) {}

template <Scalar T>
T Point<T>::x() const { return x_; }

template <Scalar T>
T Point<T>::y() const { return y_; }

template <Scalar T>
void Point<T>::set_x(T x) { x_ = x; }

template <Scalar T>
void Point<T>::set_y(T y) { y_ = y; }

template <Scalar T>
bool Point<T>::operator==(const Point<T>& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

