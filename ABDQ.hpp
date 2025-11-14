#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t front_;
    std::size_t back_;

    void ensureCapacity() {
        if (size_ < capacity_) return;
        std::size_t newCapacity = capacity_ * 2;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i)
            newData[i] = data_[(front_ + i) % capacity_];
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
    }

public:
    // Big Five
    ABDQ(std::size_t capacity = 4)
        : data_(new T[capacity > 0 ? capacity : 4]),
          capacity_(capacity > 0 ? capacity : 4),
          size_(0), front_(0), back_(0) {}

    ~ABDQ() { delete[] data_; }

    ABDQ(const ABDQ& other)
        : data_(new T[other.capacity_]),
          capacity_(other.capacity_),
          size_(other.size_),
          front_(0),
          back_(other.size_)
    {
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = 0;
        back_ = size_;
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        return *this;
    }

    ABDQ(ABDQ&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_),
          front_(other.front_), back_(other.back_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = other.back_ = 0;
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
        other.size_ = other.capacity_ = 0;
        other.front_ = other.back_ = 0;
        return *this;
    }

    // Interface methods
    void pushFront(const T& item) override {
        ensureCapacity();
        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        ++size_;
    }

    void pushBack(const T& item) override {
        ensureCapacity();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    void popFront() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        front_ = (front_ + 1) % capacity_;
        --size_;
    }

    void popBack() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        --size_;
    }

    T& front() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return data_[front_];
    }

    T& back() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return data_[(back_ == 0 ? capacity_ : back_) - 1];
    }

    bool isEmpty() const override { return size_ == 0; }

    std::size_t getSize() const noexcept override { return size_; }
};
