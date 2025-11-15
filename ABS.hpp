#pragma once

#include <stdexcept>

template <typename T>
class ABS {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t initial_capacity_;
    std::size_t curr_size_;

    void resize(std::size_t newCapacity) {
        T* newArray = new T[newCapacity];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            newArray[i] = array_[i];
        }
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
    }

public:
    ABS() : capacity_(1), initial_capacity_(1), curr_size_(0) {
        array_ = new T[capacity_];
    }

    ABS(const ABS& other)
        : capacity_(other.capacity_), initial_capacity_(other.initial_capacity_),
          curr_size_(other.curr_size_) {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            array_[i] = other.array_[i];
        }
    }

    ABS(ABS&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_),
          initial_capacity_(other.initial_capacity_), curr_size_(other.curr_size_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ~ABS() {
        delete[] array_;
    }

    void push(const T& value) {
        if (curr_size_ == capacity_) {
            resize(capacity_ * 2);
        }
        array_[curr_size_++] = value;
    }

    T pop() {
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

    T peek() const {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        return array_[curr_size_ - 1];
    }

    std::size_t getSize() const {
        return curr_size_;
    }

    std::size_t getMaxCapacity() const {
        return capacity_;
    }
};


