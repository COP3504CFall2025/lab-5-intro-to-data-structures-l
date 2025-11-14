#pragma once
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;
    std::size_t capacity_;
    std::size_t front_;
    std::size_t back_;
    std::size_t size_;

    void resize() {
        std::size_t newCap = capacity_ * 2;
        T* newData = new T[newCap];


        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCap;
        front_ = 0;
        back_ = size_;
    }

public:
    explicit ABDQ(std::size_t capacity = 4)
        : data_(new T[capacity > 0 ? capacity : 4]),
          capacity_(capacity > 0 ? capacity : 4),
          front_(0),
          back_(0),
          size_(0) {}

    ~ABDQ() {
        delete[] data_;
    }

    ABDQ(const ABDQ& other)
        : data_(new T[other.capacity_]),
          capacity_(other.capacity_),
          front_(0),
          back_(other.size_),
          size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
    }

    ABDQ(ABDQ&& other) noexcept
        : data_(other.data_),
          capacity_(other.capacity_),
          front_(other.front_),
          back_(other.back_),
          size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }


    void pushFront(const T& item) override {
        if (size_ == capacity_)
            resize();
        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        ++size_;
    }

    void pushBack(const T& item) override {
        if (size_ == capacity_)
            resize();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }


    T popFront() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        T value = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return value;
    }

    T popBack() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T value = data_[back_];
        --size_;
        return value;
    }


    T& front() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        return data_[front_];
    }

    T& back() override {
        if (isEmpty())
            throw std::runtime_error("Deque empty");
        std::size_t lastIndex = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        return data_[lastIndex];
    }

    std::size_t getSize() const override {
        return size_;
    }

    bool isEmpty() const override {
        return size_ == 0;
    }
};
