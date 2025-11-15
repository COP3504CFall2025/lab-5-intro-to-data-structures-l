#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

template <typename T>
class ABQ : public QueueInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t curr_size_;
    std::size_t front_;
    std::size_t back_;

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
    ABQ() : capacity_(1), curr_size_(0), front_(0), back_(0) {
        array_ = new T[1];
    }

    ABQ(std::size_t capacity) : capacity_(capacity), curr_size_(0), front_(0), back_(0) {
        if (capacity_ == 0) capacity_ = 1;
        array_ = new T[capacity_];
    }

    ABQ(const ABQ& other)
        : capacity_(other.capacity_), curr_size_(other.curr_size_),
          front_(other.front_), back_(other.back_) {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < capacity_; i++) array_[i] = other.array_[i];
    }

    ABQ(ABQ&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_),
          front_(other.front_), back_(other.back_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABQ& operator=(const ABQ& other) {
        if (this != &other) {
            delete[] array_;
            capacity_ = other.capacity_;
            curr_size_ = other.curr_size_;
            front_ = other.front_;
            back_ = other.back_;
            array_ = new T[capacity_];
            for (std::size_t i = 0; i < capacity_; i++) array_[i] = other.array_[i];
        }
        return *this;
    }

    ABQ& operator=(ABQ&& other) noexcept {
        if (this != &other) {
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
        }
        return *this;
    }

    ~ABQ() { delete[] array_; }

    void enqueue(const T& value) {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[back_] = value;
        back_ = (back_ + 1) % capacity_;
        curr_size_++;
    }

    T dequeue() {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        T val = array_[front_];
        front_ = (front_ + 1) % capacity_;
        curr_size_--;
        return val;
    }

    T& peek() {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        return array_[front_];
    }

    std::size_t getSize() const { return curr_size_; }
    bool isEmpty() const { return curr_size_ == 0; }

    // Optional helper functions
    std::size_t getMaxCapacity() const { return capacity_; }
    void PrintForward() const {
        for (std::size_t i = 0; i < curr_size_; i++)
            std::cout << array_[(front_ + i) % capacity_] << (i + 1 < curr_size_ ? " " : "");
    }
    void PrintReverse() const {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::size_t idx = (front_ + curr_size_ - 1 - i) % capacity_;
            std::cout << array_[idx] << (i + 1 < curr_size_ ? " " : "");
        }
    }
};

