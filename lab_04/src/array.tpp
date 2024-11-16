#pragma once

#include "array.hpp"

#include <stdexcept>

template <class T>
Array<T>::Array()
    : size_(0), capacity_(1)
{
    figures_ = std::shared_ptr<T[]>(new T[capacity_]);
}

template <class T>
Array<T>::~Array() {}

template <class T>
T &Array<T>::operator[](std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return figures_[index];
}

template <class T>
Array<T>::operator double() const
{
    double sum = 0;
    for (std::size_t i = 0; i < size_; ++i)
    {
        sum += static_cast<double>(*figures_[i]);
    }
    return sum;
}

template <class T>
void Array<T>::print(std::ostream &os) const
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        os << "Figure " << i << ":" << std::endl;
        os << *figures_[i];
        os << "Geometric center: " << figures_[i]->center() << std::endl;
        os << "Area: " << static_cast<double>(*figures_[i]) << std::endl
           << std::endl;
    }
}

template <class T>
void Array<T>::push_back(const T &figure)
{
    if (size_ >= capacity_)
    {
        resize();
    }

    figures_[size_] = figure;
    ++size_;
}

template <class T>
void Array<T>::erase(std::size_t index)
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

template <class T>
std::size_t Array<T>::size() const
{
    return size_;
}

template <class T>
T &Array<T>::begin()
{
    if (size_ == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    return *figures_[0];
}

template <class T>
T &Array<T>::end()
{
    if (size_ == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    return *figures_[size_ - 1];
}

template <class T>
void Array<T>::resize()
{
    capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;

    std::shared_ptr<T[]> new_figures(new T[capacity_]);

    for (std::size_t i = 0; i < size_; ++i)
    {
        new_figures[i] = std::move(figures_[i]);
    }

    figures_ = new_figures;
}