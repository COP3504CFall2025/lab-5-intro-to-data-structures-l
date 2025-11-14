#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template<typename T>
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
    ABDQ() : data_(new T[1]), capacity_(1), size_(0), front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity)
        : data_(new T[capacity > 0 ? capacity : 1]), capacity_(capacity > 0 ? capacity : 1), size_(0), front_(0), back_(0) {}

    ABDQ(const ABDQ& other)
        : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }

    ABDQ(ABDQ&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.capacity_];
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = 0;
            back_ = size_;
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[(other.front_ + i) % other.capacity_];
            }
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = other.front_;
            back_ = other.back_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
            other.front_ = 0;
            other.back_ = 0;
        }
        return *this;
    }

    ~ABDQ() { delete[] data_; }

    void pushFront(const T& item) override {
        if (size_ == capacity_) resize();
        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        ++size_;
    }

    void pushBack(const T& item) override {
        if (size_ == capacity_) resize();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    T popFront() override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        T item = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return item;
    }

    T popBack() override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T item = data_[back_];
        --size_;
        return item;
    }

    const T& front() const override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        std::size_t lastIndex = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        return data_[lastIndex];
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }
};
