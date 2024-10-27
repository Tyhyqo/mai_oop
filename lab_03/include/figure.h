#pragma once

#include <iostream>

class Figure
{
public:
    virtual operator double() const = 0;
    
    virtual std::pair<double, double> center() const = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;

    virtual ~Figure() = default;

protected:
    virtual bool validateFigure() = 0;
    virtual double area() const = 0;
};

inline std::ostream &operator<<(std::ostream &os, const Figure &fig)
{
    fig.print(os);
    return os;
}

inline std::istream &operator>>(std::istream &is, Figure &fig)
{
    fig.read(is);
    return is;
}