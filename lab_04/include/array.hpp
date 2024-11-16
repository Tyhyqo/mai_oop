#pragma once

#include <memory>

template <class T>
class Array
{

public:
    Array();
    ~Array();

    T &operator[](std::size_t index);
    operator double() const;

    void print(std::ostream &os) const;
    void push_back(const T &figure);
    void erase(std::size_t index);
    std::size_t size() const;
    T &begin();
    T &end();

private:
    void resize();

    std::shared_ptr<T[]> figures_;
    std::size_t size_;
    std::size_t capacity_;
};

template <class T>
inline std::ostream &operator<<(std::ostream &os, const Array<T> &figVec)
{
    figVec.print(os);
    return os;
}

#include "array.tpp"
