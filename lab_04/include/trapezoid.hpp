#pragma once

#include "figure.hpp"
#include "point.hpp"

#include <array>
#include <memory>

template <Scalar T>
class Trapezoid : public Figure<T>
{
public:
    Trapezoid();
    Trapezoid(const std::array<Point<T>, 4> &points);
    Trapezoid(const Trapezoid<T> &other);
    Trapezoid(Trapezoid<T> &&other) noexcept;

    Trapezoid<T> &operator=(const Trapezoid<T> &other);
    Trapezoid<T> &operator=(Trapezoid<T> &&other) noexcept;
    bool operator==(const Trapezoid<T> &other) const;
    operator double() const override;

    Point<T> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

    ~Trapezoid() override = default;

protected:
    bool validateFigure() override;
    double area() const override;

private:
    std::array<std::unique_ptr<Point<T>>, 4> points_;
};

#include "trapezoid.tpp"