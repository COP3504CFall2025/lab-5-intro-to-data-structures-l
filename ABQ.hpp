#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t curr_size_;
    const std::size_t initial_capacity_;

    void resize(std::size_t new_cap) {
        T* newArr = new T[new_cap];
        for (std::size_t i = 0; i < curr_size_; i++) {
            newArr[i] = array_[i];
        }
        delete[] array_;
        array_ = newArr;
        capacity_ = new_cap;
    }

public:
    ABS() : capacity_(1), curr_size_(0), initial_capacity_(1) {
        array_ = new T[capacity_];
    }

    ABS(std::size_t capacity) : capacity_(capacity ? capacity : 1), curr_size_(0), initial_capacity_(capacity ? capacity : 1) {
        array_ = new T[capacity_];
    }

    ABS(const ABS& other) : capacity_(other.capacity_), curr_size_(other.curr_size_), initial_capacity_(other.initial_capacity_) {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; i++) array_[i] = other.array_[i];
    }

    ABS(ABS&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_), initial_capacity_(other.initial_capacity_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABS& operator=(const ABS& other) {
        if (this == &other) return *this;
        delete[] array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; i++) array_[i] = other.array_[i];
        return *this;
    }

    ABS& operator=(ABS&& other) noexcept {
        if (this == &other) return *this;
        delete[] array_;
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        return *this;
    }

    ~ABS() {
        delete[] array_;
    }

    void push(const T& item) override {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[curr_size_++] = item;
    }

    T pop() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        T val = array_[--curr_size_];
        // Optional shrink logic (not below initial capacity)
        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4 && capacity_ / 2 >= initial_capacity_) {
            resize(capacity_ / 2);
        }
        return val;
    }

    T& peek() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        return array_[curr_size_ - 1];
    }

    std::size_t getSize() const override {
        return curr_size_;
    }

    bool isEmpty() const override {
        return curr_size_ == 0;
    }

    // For autograder
    std::size_t getMaxCapacity() const {
        return capacity_;
    }

    void PrintForward() const {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i];
            if (i + 1 < curr_size_) std::cout << " ";
        }
        std::cout << std::endl;
    }

    void PrintReverse() const {
        for (std::size_t i = curr_size_; i > 0; i--) {
            std::cout << array_[i - 1];
            if (i > 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
};
