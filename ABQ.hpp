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
    std::size_t initial_capacity_;
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
    ABQ() : capacity_(1), initial_capacity_(1), curr_size_(0), front_(0), back_(0) {
        array_ = new T[capacity_];
    }

    ABQ(std::size_t capacity) : capacity_(capacity), initial_capacity_(capacity), curr_size_(0), front_(0), back_(0) {
        if (capacity_ == 0) capacity_ = initial_capacity_ = 1;
        array_ = new T[capacity_];
    }

    ~ABQ() { delete[] array_; }

    void enqueue(const T& value) override {
        if (curr_size_ == capacity_) {
            resize(capacity_ * 2);
        }
        array_[back_] = value;
        back_ = (back_ + 1) % capacity_;
        curr_size_++;
    }

    T dequeue() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        T val = array_[front_];
        front_ = (front_ + 1) % capacity_;
        curr_size_--;

        // Shrink if quarter full but never below initial capacity
        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4 && capacity_ > initial_capacity_) {
            std::size_t newCap = capacity_ / 2;
            if (newCap < initial_capacity_) newCap = initial_capacity_;
            resize(newCap);
        }

        return val;
    }

    T& peek() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        return array_[front_];
    }

    std::size_t getSize() const override { return curr_size_; }

    bool isEmpty() const override { return curr_size_ == 0; }

    void PrintForward() const {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[(front_ + i) % capacity_] << " ";
        }
        std::cout << std::endl;
    }

    void PrintReverse() const {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::size_t idx = (front_ + curr_size_ - 1 - i) % capacity_;
            std::cout << array_[idx] << " ";
        }
        std::cout << std::endl;
    }

    std::size_t getMaxCapacity() const { return capacity_; }
};
