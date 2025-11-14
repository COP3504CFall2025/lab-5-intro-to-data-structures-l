#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABQ : public QueueInterface<T> {
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
    ABQ(std::size_t capacity = 1)
        : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}

    ~ABQ() { delete[] data_; }

    ABQ(const ABQ& other)
        : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.size_)
    {
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
    }

    ABQ& operator=(const ABQ& other) {
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

    ABQ(ABQ&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_)
    {
        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
        other.front_ = other.back_ = 0;
    }

    ABQ& operator=(ABQ&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
        other.front_ = other.back_ = 0;
        return *this;
    }

    // Interface methods
    void enqueue(const T& item) override {
        ensureCapacity();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    T dequeue() override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        T val = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return val;
    }

    T peek() const override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return data_[front_];
    }

    std::size_t getSize() const noexcept override { return size_; }

    bool isEmpty() const { return size_ == 0; }
};
