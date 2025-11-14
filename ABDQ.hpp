#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t front_;
    std::size_t back_;
    static constexpr std::size_t SCALE_FACTOR = 2;

    void resize() {
        std::size_t newCapacity = capacity_ * SCALE_FACTOR;
        T* newData = new T[newCapacity];

        // Copy elements in order
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
    }

public:
    // Big 5
    ABDQ() : capacity_(1), size_(0), data_(new T[1]), front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity) : capacity_(capacity > 0 ? capacity : 1), size_(0),
                                         data_(new T[capacity_]), front_(0), back_(0) {}

    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_),
                               data_(new T[other.capacity_]), front_(other.front_), back_(other.back_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[(front_ + i) % capacity_] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }

    ABDQ(ABDQ&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_),
          front_(other.front_), back_(other.back_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;
        T* newData = new T[other.capacity_];
        for (std::size_t i = 0; i < other.size_; ++i) {
            newData[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = 0;
        back_ = size_;
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }

    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ >= capacity_) resize();
        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        ++size_;
    }

    void pushBack(const T& item) override {
        if (size_ >= capacity_) resize();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        T item = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return item;
    }

    T popBack() override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T item = data_[back_];
        --size_;
        return item;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        std::size_t idx = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        return data_[idx];
    }

    // Getters
    std::size_t getSize() const noexcept override { return size_; }
};
