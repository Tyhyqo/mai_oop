#pragma once

#include "figure.hpp"
#include "point.hpp"

#include <array>
#include <memory>

template <Scalar T>
class Rhomb : public Figure<T>
{
public:
    Rhomb();
    Rhomb(const std::array<Point<T>, 4> &points);
    Rhomb(const Rhomb<T> &other);
    Rhomb(Rhomb<T> &&other) noexcept;

    Rhomb<T> &operator=(const Rhomb<T> &other);
    Rhomb<T> &operator=(Rhomb<T> &&other) noexcept;
    bool operator==(const Rhomb<T> &other) const;
    operator double() const override;

    Point<T> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

    ~Rhomb() override = default;

protected:
    bool validateFigure() override;
    double area() const override;

private:
    std::array<std::unique_ptr<Point<T>>, 4> points_;
};

#include "rhomb.tpp"
