#include "dynamic_array.hpp"

// Реализация методов класса DynamicArray

template<typename T>
DynamicArray<T>::DynamicArray(const allocator_type& alloc)
    : allocator_(alloc), data_(nullptr), size_(0), capacity_(10) {
    data_ = allocator_.allocate(capacity_);
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    clear();
    allocator_.deallocate(data_, capacity_);
}

template<typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }
    allocator_.construct(data_ + size_, value);
    ++size_;
}

template<typename T>
void DynamicArray<T>::push_back(T&& value) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }
    allocator_.construct(data_ + size_, std::move(value));
    ++size_;
}

template<typename T>
void DynamicArray<T>::reserve(std::size_t new_capacity) {
    if (new_capacity > capacity_) {
        T* new_data = allocator_.allocate(new_capacity);
        for (std::size_t i = 0; i < size_; ++i) {
            allocator_.construct(new_data + i, std::move(data_[i]));
            allocator_.destroy(data_ + i);
        }
        allocator_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_capacity;
    }
}

template<typename T>
void DynamicArray<T>::clear() {
    for (std::size_t i = 0; i < size_; ++i) {
        allocator_.destroy(data_ + i);
    }
    size_ = 0;
}

template<typename T>
T& DynamicArray<T>::operator[](std::size_t index) {
    return data_[index];
}

template<typename T>
const T& DynamicArray<T>::operator[](std::size_t index) const {
    return data_[index];
}

template<typename T>
std::size_t DynamicArray<T>::size() const {
    return size_;
}

// Реализация итератора

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() {
    return Iterator(data_);
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() {
    return Iterator(data_ + size_);
}

template<typename T>
DynamicArray<T>::Iterator::Iterator(pointer ptr) : ptr_(ptr) {}

template<typename T>
typename DynamicArray<T>::Iterator::reference DynamicArray<T>::Iterator::operator*() const {
    return *ptr_;
}

template<typename T>
typename DynamicArray<T>::Iterator::pointer DynamicArray<T>::Iterator::operator->() {
    return ptr_;
}

template<typename T>
typename DynamicArray<T>::Iterator& DynamicArray<T>::Iterator::operator++() {
    ++ptr_;
    return *this;
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++ptr_;
    return temp;
}