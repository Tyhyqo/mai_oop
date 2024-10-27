#pragma once

#include <array>
#include "figure.h"

class Rhomb : public Figure
{
public:
    Rhomb();
    Rhomb(const std::array<std::pair<double, double>, 4> &points);
    Rhomb(const Rhomb &other);
    Rhomb(Rhomb &&other) noexcept;

    Rhomb &operator=(const Rhomb &other);
    Rhomb &operator=(Rhomb &&other) noexcept;
    bool operator==(const Rhomb &other) const;
    operator double() const override;

    std::pair<double, double> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

    ~Rhomb() override = default;

protected:
    bool validateFigure() override;
    double area() const override;

private:
    std::array<std::pair<double, double>, 4> points_;
};