#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template <typename T>
class ABQ : public QueueInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t initial_capacity_;
    std::size_t front_;
    std::size_t rear_;
    std::size_t curr_size_;

    void resize(std::size_t newCap) {
        T* newArr = new T[newCap];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            newArr[i] = array_[(front_ + i) % capacity_];
        }
        delete[] array_;
        array_ = newArr;
        capacity_ = newCap;
        front_ = 0;
        rear_ = curr_size_;
    }

public:
    // Default constructor
    ABQ() : capacity_(1), initial_capacity_(1), front_(0), rear_(0), curr_size_(0) {
        array_ = new T[capacity_];
    }

    // Destructor
    ~ABQ() { delete[] array_; }

    // Copy constructor
    ABQ(const ABQ& other)
        : capacity_(other.capacity_), initial_capacity_(other.initial_capacity_),
          front_(0), rear_(other.curr_size_), curr_size_(other.curr_size_)
    {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; ++i)
            array_[i] = other.array_[(other.front_ + i) % other.capacity_];
    }

    // Move constructor
    ABQ(ABQ&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_), initial_capacity_(other.initial_capacity_),
          front_(other.front_), rear_(other.rear_), curr_size_(other.curr_size_)
    {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.rear_ = 0;
    }

    // Move assignment
    ABQ& operator=(ABQ&& other) noexcept {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            capacity_ = other.capacity_;
            initial_capacity_ = other.initial_capacity_;
            front_ = other.front_;
            rear_ = other.rear_;
            curr_size_ = other.curr_size_;

            other.array_ = nullptr;
            other.curr_size_ = 0;
            other.capacity_ = 0;
            other.front_ = 0;
            other.rear_ = 0;
        }
        return *this;
    }

    void enqueue(const T& item) override {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[rear_] = item;
        rear_ = (rear_ + 1) % capacity_;
        ++curr_size_;
    }

    T dequeue() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue empty");
        T val = array_[front_];
        front_ = (front_ + 1) % capacity_;
        --curr_size_;

        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4 && capacity_ > initial_capacity_) {
            std::size_t newCap = capacity_ / 2;
            if (newCap < initial_capacity_) newCap = initial_capacity_;
            resize(newCap);
        }
        return val;
    }

    T& peek() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue empty");
        return array_[front_];
    }

    std::size_t getSize() const override { return curr_size_; }

    bool isEmpty() const override { return curr_size_ == 0; }

    std::size_t getMaxCapacity() const { return capacity_; }
};
