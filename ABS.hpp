#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t initial_capacity_;
    std::size_t curr_size_;

    void resize(std::size_t new_cap) {
        T* newArr = new T[new_cap];
        for (std::size_t i = 0; i < curr_size_; i++) newArr[i] = array_[i];
        delete[] array_;
        array_ = newArr;
        capacity_ = new_cap;
    }

public:
    ABS() : capacity_(1), initial_capacity_(1), curr_size_(0) {
        array_ = new T[capacity_];
    }

    ABS(std::size_t capacity) : capacity_(capacity), initial_capacity_(capacity), curr_size_(0) {
        if (capacity_ == 0) capacity_ = initial_capacity_ = 1;
        array_ = new T[capacity_];
    }

    ~ABS() { delete[] array_; }

    void push(const T& item) override {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[curr_size_++] = item;
    }

    T pop() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        T val = array_[--curr_size_];

        // Shrink if quarter full but never below initial capacity
        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4 && capacity_ > initial_capacity_) {
            std::size_t newCap = capacity_ / 2;
            if (newCap < initial_capacity_) newCap = initial_capacity_;
            resize(newCap);
        }

        return val;
    }

    T& peek() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        return array_[curr_size_ - 1];
    }

    std::size_t getSize() const override { return curr_size_; }

    bool isEmpty() const override { return curr_size_ == 0; }

    void PrintForward() const {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << (i + 1 < curr_size_ ? " " : "");
        }
        std::cout << std::endl;
    }

    void PrintReverse() const {
        for (std::size_t i = curr_size_; i > 0; i--) {
            std::cout << array_[i - 1] << (i > 1 ? " " : "");
        }
        std::cout << std::endl;
    }

    std::size_t getMaxCapacity() const { return capacity_; }
};
