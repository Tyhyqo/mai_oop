#pragma once

#include "figure.hpp"
#include "point.hpp"

#include <array>
#include <memory>

template <Scalar T>
class Rectangle : public Figure<T>
{
public:
    Rectangle();
    Rectangle(const std::array<Point<T>, 4> &points);
    Rectangle(const Rectangle<T> &other);
    Rectangle(Rectangle<T> &&other) noexcept;

    Rectangle<T> &operator=(const Rectangle<T> &other);
    Rectangle<T> &operator=(Rectangle<T> &&other) noexcept;
    bool operator==(const Rectangle<T> &other) const;
    operator double() const override;

    Point<T> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

    ~Rectangle() override = default;

protected:
    bool validateFigure() override;
    double area() const override;

private:
    std::array<std::unique_ptr<Point<T>>, 4> points_;
};


#include "rectangle.tpp"