#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template<typename T>
class ABQ : public QueueInterface<T> {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t front_;
    std::size_t back_;
    static constexpr std::size_t SCALE_FACTOR = 2;

    void resize() {
        std::size_t newCapacity = capacity_ * SCALE_FACTOR;
        T* newArray = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) {
            newArray[i] = array_[(front_ + i) % capacity_];
        }
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
    }

public:
    ABQ() : capacity_(1), size_(0), front_(0), back_(0), array_(new T[1]) {}
    explicit ABQ(std::size_t capacity)
        : capacity_(capacity > 0 ? capacity : 1), size_(0), front_(0), back_(0), array_(new T[capacity_]) {}

    ABQ(const ABQ& other)
        : capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.size_), array_(new T[other.capacity_]) {
        for (std::size_t i = 0; i < size_; ++i) {
            array_[i] = other.array_[(other.front_ + i) % other.capacity_];
        }
    }

    ABQ(ABQ&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        other.array_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABQ& operator=(const ABQ& other) {
        if (this != &other) {
            delete[] array_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = 0;
            back_ = size_;
            array_ = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                array_[i] = other.array_[(other.front_ + i) % other.capacity_];
            }
        }
        return *this;
    }

    ABQ& operator=(ABQ&& other) noexcept {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = other.front_;
            back_ = other.back_;
            other.array_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
            other.front_ = 0;
            other.back_ = 0;
        }
        return *this;
    }

    ~ABQ() {
        delete[] array_;
    }

    void enqueue(const T& item) override {
        if (size_ == capacity_) resize();
        array_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    T dequeue() override {
        if (size_ == 0) throw std::runtime_error("Queue is empty");
        T item = array_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return item;
    }

    T peek() const override {
        if (size_ == 0) throw std::runtime_error("Queue is empty");
        return array_[front_];
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }
};
