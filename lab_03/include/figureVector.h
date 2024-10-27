#pragma once

#include "figure.h"

class FigureVector
{

public:
    FigureVector();
    ~FigureVector();

    Figure &operator[](std::size_t index);
    operator double() const;

    void print(std::ostream &os) const;
    void push_back(Figure &figure);
    void erase(std::size_t index);
    std::size_t size() const;
    Figure &begin();
    Figure &end();

private:
    void resize();

    Figure **figures_;
    std::size_t size_;
    std::size_t capacity_;
};

inline std::ostream &operator<<(std::ostream &os, const FigureVector &figVec)
{
    figVec.print(os);
    return os;
}