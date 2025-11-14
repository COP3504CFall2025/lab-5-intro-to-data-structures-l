#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

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

    void shrinkIfNeeded() {
        if (capacity_ <= 4 || size_ * 4 >= capacity_) return;

        std::size_t newCapacity = capacity_ / 2;
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

    ABDQ() : capacity_(4), size_(0), front_(0), back_(0) {
        data_ = new T[capacity_];
    }


    ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0) {
        data_ = new T[capacity_];
    }


    ~ABDQ() { delete[] data_; }


    ABDQ(const ABDQ& other)
        : capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.size_) {
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = 0;
        back_ = size_;
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];

        return *this;
    }


    ABDQ(ABDQ&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_),
          front_(other.front_), back_(other.back_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
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
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }


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

    T popFront() override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        T value = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        shrinkIfNeeded();
        return value;
    }

    T popBack() override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T value = data_[back_];
        --size_;
        shrinkIfNeeded();
        return value;
    }

    const T& front() const override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) throw std::out_of_range("Deque is empty");
        return data_[(back_ == 0) ? capacity_ - 1 : back_ - 1];
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }
};
