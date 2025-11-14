#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T> {
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    size_t front_idx_;
    size_t back_idx_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[1]), front_idx_(0), back_idx_(0) {}
    explicit ABQ(const size_t capacity)
        : capacity_(capacity > 0 ? capacity : 1), curr_size_(0), array_(new T[capacity_]), front_idx_(0), back_idx_(0) {}

    ABQ(const ABQ& other)
        : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]),
          front_idx_(other.front_idx_), back_idx_(other.back_idx_) {
        for (size_t i = 0; i < curr_size_; ++i)
            array_[(front_idx_ + i) % capacity_] = other.array_[(other.front_idx_ + i) % capacity_];
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) return *this;
        T* newArray = new T[rhs.capacity_];
        for (size_t i = 0; i < rhs.curr_size_; ++i)
            newArray[i] = rhs.array_[(rhs.front_idx_ + i) % rhs.capacity_];
        delete[] array_;
        array_ = newArray;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_idx_ = 0;
        back_idx_ = curr_size_;
        return *this;
    }

    ABQ(ABQ&& other) noexcept
        : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_),
          front_idx_(other.front_idx_), back_idx_(other.back_idx_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_idx_ = 0;
        other.back_idx_ = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) return *this;
        delete[] array_;
        array_ = rhs.array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_idx_ = rhs.front_idx_;
        back_idx_ = rhs.back_idx_;
        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.front_idx_ = 0;
        rhs.back_idx_ = 0;
        return *this;
    }

    ~ABQ() noexcept override {
        delete[] array_;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }
    [[nodiscard]] T* getData() const noexcept { return array_; }

    // Insert at back
    void enqueue(const T& data) override {
        if (curr_size_ >= capacity_) resize();
        array_[back_idx_] = data;
        back_idx_ = (back_idx_ + 1) % capacity_;
        ++curr_size_;
    }

    // Access front
    T peek() const override {
        if (curr_size_ == 0) throw std::out_of_range("Queue is empty");
        return array_[front_idx_];
    }

    // Remove from front
    T dequeue() override {
        if (curr_size_ == 0) throw std::out_of_range("Queue is empty");
        T result = array_[front_idx_];
        front_idx_ = (front_idx_ + 1) % capacity_;
        --curr_size_;
        return result;
    }

private:
    void resize() {
        size_t newCapacity = capacity_ * scale_factor_;
        T* newArray = new T[newCapacity];
        for (size_t i = 0; i < curr_size_; ++i)
            newArray[i] = array_[(front_idx_ + i) % capacity_];
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
        front_idx_ = 0;
        back_idx_ = curr_size_;
    }
};


