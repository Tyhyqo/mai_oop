#pragma once

#include <array>
#include "figure.h"

class Rectangle : public Figure
{
public:
    Rectangle();
    Rectangle(const std::array<std::pair<double, double>, 4>& points);
    Rectangle(const Rectangle &other);
    Rectangle(Rectangle &&other) noexcept;

    Rectangle &operator=(const Rectangle &other);
    Rectangle &operator=(Rectangle &&other) noexcept;
    bool operator==(const Rectangle &other) const;
    operator double() const override;

    std::pair<double, double> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

    ~Rectangle() override = default;

protected:
    
    bool validateFigure() override;
    double area() const override;

private:
    std::array<std::pair<double, double>, 4> points_;
};