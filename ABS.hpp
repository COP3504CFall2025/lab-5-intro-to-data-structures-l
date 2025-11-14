#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* data_;
    std::size_t capacity_;
    std::size_t size_;

    void ensureCapacity() {
        if (size_ < capacity_) return;
        std::size_t newCapacity = capacity_ * 2;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i)
            newData[i] = data_[i];
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    // Big Five
    ABS(std::size_t capacity = 1)
        : data_(new T[capacity]), capacity_(capacity), size_(0) {}

    ~ABS() { delete[] data_; }

    ABS(const ABS& other)
        : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_)
    {
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    ABS& operator=(const ABS& other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
        return *this;
    }

    ABS(ABS&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_)
    {
        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
    }

    ABS& operator=(ABS&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
        return *this;
    }

    // Interface methods
    void push(const T& item) override {
        ensureCapacity();
        data_[size_++] = item;
    }

    T pop() override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return data_[--size_];
    }

    T peek() const override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return data_[size_ - 1];
    }

    std::size_t getSize() const noexcept override { return size_; }

    bool isEmpty() const { return size_ == 0; }
};
