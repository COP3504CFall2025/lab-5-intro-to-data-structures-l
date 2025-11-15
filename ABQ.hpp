#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

template <typename T>
class ABQ : public QueueInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t curr_size_;
    std::size_t front_;
    std::size_t back_;
    const std::size_t initial_capacity_;

    void resize(std::size_t new_cap) {
        T* new_array = new T[new_cap];
        for (std::size_t i = 0; i < curr_size_; i++) {
            new_array[i] = array_[(front_ + i) % capacity_];
        }
        delete[] array_;
        array_ = new_array;
        capacity_ = new_cap;
        front_ = 0;
        back_ = curr_size_;
    }

public:
    ABQ() : capacity_(1), curr_size_(0), front_(0), back_(0), initial_capacity_(1) {
        array_ = new T[capacity_];
    }

    ABQ(std::size_t capacity)
        : capacity_(capacity ? capacity : 1), curr_size_(0), front_(0), back_(0), initial_capacity_(capacity ? capacity : 1) {
        array_ = new T[capacity_];
    }

    ABQ(const ABQ& other)
        : capacity_(other.capacity_), curr_size_(other.curr_size_), front_(other.front_), back_(other.back_), initial_capacity_(other.initial_capacity_) {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < capacity_; i++) array_[i] = other.array_[i];
    }

    ABQ(ABQ&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_), front_(other.front_), back_(other.back_), initial_capacity_(other.initial_capacity_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABQ& operator=(const ABQ& other) {
        if (this == &other) return *this;
        delete[] array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        front_ = other.front_;
        back_ = other.back_;
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < capacity_; i++) array_[i] = other.array_[i];
        return *this;
    }

    ABQ& operator=(ABQ&& other) noexcept {
        if (this == &other) return *this;
        delete[] array_;
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        front_ = other.front_;
        back_ = other.back_;
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }

    ~ABQ() {
        delete[] array_;
    }

    void enqueue(const T& value) override {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[back_] = value;
        back_ = (back_ + 1) % capacity_;
        curr_size_++;
    }

    T dequeue() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        T val = array_[front_];
        front_ = (front_ + 1) % capacity_;
        curr_size_--;
        // Optional shrink
        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4 && capacity_ / 2 >= initial_capacity_) {
            resize(capacity_ / 2);
        }
        return val;
    }

    T& peek() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        return array_[front_];
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
            std::cout << array_[(front_ + i) % capacity_];
            if (i + 1 < curr_size_) std::cout << " ";
        }
        std::cout << std::endl;
    }

    void PrintReverse() const {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::size_t idx = (front_ + curr_size_ - 1 - i) % capacity_;
            std::cout << array_[idx];
            if (i + 1 < curr_size_) std::cout << " ";
        }
        std::cout << std::endl;
    }
};
