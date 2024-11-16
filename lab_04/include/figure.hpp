#pragma once

#include "point.hpp"

#include <memory>
#include <iostream>

template <Scalar T>
class Figure
{
public:
    virtual operator double() const = 0;

    virtual Point<T> center() const = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;

    virtual ~Figure() = default;

protected:
    virtual bool validateFigure() = 0;
    virtual double area() const = 0;
};

template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Figure<T> &fig)
{
    fig.print(os);
    return os;
}

template <Scalar T>
inline std::istream &operator>>(std::istream &is, Figure<T> &fig)
{
    fig.read(is);
    return is;
}