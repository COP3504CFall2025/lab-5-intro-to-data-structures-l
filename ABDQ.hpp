#pragma once
#include "Interfaces.hpp"
#include <stdexcept>
#include <cstddef>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;
    size_t capacity_;
    size_t size_;
    size_t front_;
    size_t back_;

public:

    explicit ABDQ(size_t capacity = 10)
        : capacity_(capacity > 0 ? capacity : 1),
          size_(0),
          front_(0),
          back_(0)
    {
        data_ = new T[capacity_];
    }

    ~ABDQ() {
        delete[] data_;
    }

    ABDQ(const ABDQ& other)
        : capacity_(other.capacity_),
          size_(other.size_),
          front_(other.front_),
          back_(other.back_)
    {
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; ++i)
            data_[i] = other.data_[i];
    }


    ABDQ(ABDQ&& other) noexcept
        : data_(other.data_),
          capacity_(other.capacity_),
          size_(other.size_),
          front_(other.front_),
          back_(other.back_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = other.front_;
            back_ = other.back_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < capacity_; ++i)
                data_[i] = other.data_[i];
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
        }
        return *this;
    }

    size_t getSize() const override {
        return size_;
    }

    bool isEmpty() const override {
        return size_ == 0;
    }

    void pushFront(const T& value) override {
        if (size_ == capacity_)
            throw std::runtime_error("Deque full");
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = value;
        ++size_;
    }

    void pushBack(const T& value) override {
        if (size_ == capacity_)
            throw std::runtime_error("Deque full");
        data_[back_] = value;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    void popFront() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        front_ = (front_ + 1) % capacity_;
        --size_;
    }

    void popBack() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        back_ = (back_ + capacity_ - 1) % capacity_;
        --size_;
    }

    T& front() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        return data_[front_];
    }

    T& back() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        return data_[(back_ + capacity_ - 1) % capacity_];
    }
};
