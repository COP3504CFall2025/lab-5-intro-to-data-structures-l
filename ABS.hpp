#ifndef ABS_HPP
#define ABS_HPP

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t curr_size_;

    void resize() {
        capacity_ *= 2;
        T* newArr = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; i++) newArr[i] = array_[i];
        delete[] array_;
        array_ = newArr;
    }

public:
    ABS() : capacity_(1), curr_size_(0) {
        array_ = new T[capacity_];
    }

    ABS(const std::size_t capacity) : capacity_(capacity), curr_size_(0) {
        array_ = new T[capacity_];
    }

    ABS(const ABS& other) : capacity_(other.capacity_), curr_size_(other.curr_size_) {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; i++) array_[i] = other.array_[i];
    }

    ABS(ABS&& other) noexcept : array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_) {
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
        if (curr_size_ == capacity_) resize();
        array_[curr_size_++] = item;
    }

    T pop() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        return array_[--curr_size_];
    }

    T peek() const override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        return array_[curr_size_ - 1];
    }

    std::size_t getSize() const override {
        return curr_size_;
    }

    void PrintForward() const override {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i];
            if (i + 1 < curr_size_) std::cout << " ";
        }
    }

    void PrintReverse() const override {
        for (std::size_t i = curr_size_; i > 0; i--) {
            std::cout << array_[i - 1];
            if (i > 1) std::cout << " ";
        }
    }
};

#endif
