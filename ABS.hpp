#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t initial_capacity_;
    std::size_t curr_size_;

    void resize(std::size_t newCap) {
        T* newArr = new T[newCap];
        for (std::size_t i = 0; i < curr_size_; ++i)
            newArr[i] = array_[i];
        delete[] array_;
        array_ = newArr;
        capacity_ = newCap;
    }

public:
    // Default constructor
    ABS() : capacity_(1), initial_capacity_(1), curr_size_(0) {
        array_ = new T[capacity_];
    }

    // Destructor
    ~ABS() { delete[] array_; }

    // Copy constructor
    ABS(const ABS& other)
        : capacity_(other.capacity_), initial_capacity_(other.initial_capacity_),
          curr_size_(other.curr_size_)
    {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; ++i)
            array_[i] = other.array_[i];
    }

    // Move constructor
    ABS(ABS&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_),
          initial_capacity_(other.initial_capacity_), curr_size_(other.curr_size_)
    {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }

    // Move assignment
    ABS& operator=(ABS&& other) noexcept {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            capacity_ = other.capacity_;
            initial_capacity_ = other.initial_capacity_;
            curr_size_ = other.curr_size_;

            other.array_ = nullptr;
            other.curr_size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    void push(const T& item) override {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[curr_size_++] = item;
    }

    T pop() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        --curr_size_;
        T val = array_[curr_size_];

        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4 && capacity_ > initial_capacity_) {
            std::size_t newCap = capacity_ / 2;
            if (newCap < initial_capacity_) newCap = initial_capacity_;
            resize(newCap);
        }
        return val;
    }

    T& peek() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack e_
