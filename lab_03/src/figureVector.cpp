#include "figureVector.h"
#include <stdexcept>

FigureVector::FigureVector()
    : size_(0), capacity_(1) 
{
    figures_ = new Figure*[capacity_];
}

FigureVector::~FigureVector()
{
    delete[] figures_;
}

Figure &FigureVector::operator[](std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return *figures_[index];
}

FigureVector::operator double() const
{
    double sum = 0;
    for (std::size_t i = 0; i < size_; ++i)
    {
        sum += static_cast<double>(*figures_[i]);
    }
    return sum;
}

void FigureVector::print(std::ostream &os) const
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        std::pair<double, double> figCentre = figures_[i]->center();
        os << "Figure " << i << ":" << std::endl;
        os << *figures_[i];
        os << "Geometric center: " << figCentre.first << figCentre.second << std::endl;
        os << "Area: " << static_cast<double>(*figures_[i]) << std::endl << std::endl;
    }
}

void FigureVector::push_back(Figure &figure)
{
    if (size_ >= capacity_)
    {
        resize();
    }

    figures_[size_] = &figure;
    ++size_;
}

void FigureVector::erase(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    for (std::size_t i = index; i < size_ - 1; ++i)
    {
        figures_[i] = std::move(figures_[i + 1]);
    }
    --size_;
}

std::size_t FigureVector::size() const
{
    return size_;
}

Figure &FigureVector::begin()
{
    if (size_ == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    return *figures_[0];
}

Figure &FigureVector::end()
{
    if (size_ == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    return *figures_[size_ - 1];
}

void FigureVector::resize()
{
    capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;

    Figure **new_figures = new Figure*[capacity_];
    for (std::size_t i = 0; i < size_; ++i)
    {
        new_figures[i] = std::move(figures_[i]);
    }
    
    delete[] figures_;
    figures_ = new_figures;
}