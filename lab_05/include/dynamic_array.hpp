#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <memory_resource>
#include <iterator>
#include <cstddef>
#include <utility>

template<typename T>
class DynamicArray {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;

    explicit DynamicArray(const allocator_type& alloc = {});

    ~DynamicArray();

    void push_back(const T& value);
    void push_back(T&& value);
    void reserve(std::size_t new_capacity);
    void clear();

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const;

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        Iterator(pointer ptr);

        reference operator*() const;
        pointer operator->();
        Iterator& operator++();
        Iterator operator++(int);

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.ptr_ == b.ptr_;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.ptr_ != b.ptr_;
        }

    private:
        pointer ptr_;
    };

    Iterator begin();
    Iterator end();

private:
    allocator_type allocator_;
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

#include "dynamic_array.tpp"

#endif // DYNAMIC_ARRAY_HPP