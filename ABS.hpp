#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t size_;
    static constexpr std::size_t SCALE_FACTOR = 2;

    void resize() {
        std::size_t new_capacity = capacity_ * SCALE_FACTOR;
        T* new_array = new T[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
        capacity_ = new_capacity;
    }

public:
    ABS() : array_(new T[1]), capacity_(1), size_(0) {}
    explicit ABS(std::size_t capacity) : array_(new T[capacity > 0 ? capacity : 1]),
        capacity_(capacity > 0 ? capacity : 1), size_(0) {}
    ABS(const ABS& other) : array_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }
    ABS(ABS&& other) noexcept : array_(other.array_), capacity_(other.capacity_), size_(other.size_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }
    ABS& operator=(const ABS& other) {
        if (this != &other) {
            delete[] array_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            array_ = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                array_[i] = other.array_[i];
            }
        }
        return *this;
    }
    ABS& operator=(ABS&& other) noexcept {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            other.array_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }
    ~ABS() override {
        delete[] array_;
    }

    void push(const T& item) override {
        if (size_ >= capacity_) resize();
        array_[size_++] = item;
    }

    T pop() override {
        if (size_ == 0) throw std::runtime_error("Stack is empty");
        --size_;
        return array_[size_];
    }

    T peek() const override {
        if (size_ == 0) throw std::runtime_error("Stack is empty");
        return array_[size_ - 1];
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }
};
