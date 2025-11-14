#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"


using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:

    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;


    [[nodiscard]] size_t getSize() const noexcept override;

    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    [[nodiscard]] T* getData() const noexcept;


    void push(const T& data) override;

    T peek() const override;

    T pop() override;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

template<typename T>
ABS<T>::ABS() : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}

template<typename T>
ABS<T>::ABS(const size_t capacity)
    : capacity_(capacity > 0 ? capacity : 1), curr_size_(0), array_(new T[capacity_]) {}

template<typename T>
ABS<T>::ABS(const ABS& other)
    : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]) {
    std::copy(other.array_, other.array_ + other.curr_size_, array_);
}

template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& rhs) {
    if (this == &rhs) return *this;
    T* newArray = new T[rhs.capacity_];
    std::copy(rhs.array_, rhs.array_ + rhs.curr_size_, newArray);
    delete[] array_;
    array_ = newArray;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    return *this;
}

template<typename T>
ABS<T>::ABS(ABS&& other) noexcept
    : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
    other.array_ = nullptr;
    other.capacity_ = 0;
    other.curr_size_ = 0;
}

template<typename T>
ABS<T>& ABS<T>::operator=(ABS&& rhs) noexcept {
    if (this == &rhs) return *this;
    delete[] array_;
    array_ = rhs.array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    rhs.array_ = nullptr;
    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    return *this;
}

template<typename T>
ABS<T>::~ABS() noexcept override {
    delete[] array_;
}

template<typename T>
size_t ABS<T>::getSize() const noexcept { return curr_size_; }

template<typename T>
void ABS<T>::push(const T& data) {
    if (curr_size_ >= capacity_) resize();
    array_[curr_size_++] = data;
}

template<typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0) throw std::out_of_range("Stack is empty");
    return array_[--curr_size_];
}

template<typename T>
T ABS<T>::peek() const {
    if (curr_size_ == 0) throw std::out_of_range("Stack is empty");
    return array_[curr_size_ - 1];
}

template<typename T>
size_t ABS<T>::getMaxCapacity() const noexcept { return capacity_; }

template<typename T>
T* ABS<T>::getData() const noexcept { return array_; }

template<typename T>
void ABS<T>::resize() {
    size_t newCapacity = capacity_ * scale_factor_;
    T* newArray = new T[newCapacity];
    std::copy(array_, array_ + curr_size_, newArray);
    delete[] array_;
    array_ = newArray;
    capacity_ = newCapacity;
}
