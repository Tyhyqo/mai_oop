#pragma once

#include <array>
#include "figure.h"

class Trapezoid : public Figure
{
public:
    Trapezoid();
    Trapezoid(const std::array<std::pair<double, double>, 4> &points);
    Trapezoid(const Trapezoid &other);
    Trapezoid(Trapezoid &&other) noexcept;

    Trapezoid &operator=(const Trapezoid &other);
    Trapezoid &operator=(Trapezoid &&other) noexcept;
    bool operator==(const Trapezoid &other) const;
    operator double() const override;

    std::pair<double, double> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

    ~Trapezoid() override = default;

protected:
    bool validateFigure() override;
    double area() const override;

private:
    std::array<std::pair<double, double>, 4> points_;
};