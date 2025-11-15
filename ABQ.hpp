#pragma once

#include <stdexcept>

template <typename T>
class ABQ {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t initial_capacity_;
    std::size_t front_;
    std::size_t rear_;
    std::size_t curr_size_;

    void resize(std::size_t newCapacity) {
        T* newArray = new T[newCapacity];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            newArray[i] = array_[(front_ + i) % capacity_];
        }
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
        front_ = 0;
        rear_ = curr_size_;
    }

public:
    ABQ() : capacity_(1), initial_capacity_(1), front_(0), rear_(0), curr_size_(0) {
        array_ = new T[capacity_];
    }

    ABQ(const ABQ& other)
        : capacity_(other.capacity_), initial_capacity_(other.initial_capacity_),
          front_(other.front_), rear_(other.rear_), curr_size_(other.curr_size_) {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            array_[(front_ + i) % capacity_] = other.array_[(front_ + i) % capacity_];
        }
    }

    ABQ(ABQ&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_),
          initial_capacity_(other.initial_capacity_), front_(other.front_),
          rear_(other.rear_), curr_size_(other.curr_size_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ~ABQ() {
        delete[] array_;
    }

    void enqueue(const T& value) {
        if (curr_size_ == capacity_) {
            resize(capacity_ * 2);
        }
        array_[rear_] = value;
        rear_ = (rear_ + 1) % capacity_;
        ++curr_size_;
    }

    T dequeue() {
        if (curr_size_ == 0) throw std::runtime_error("Queue empty");
        T val = array_[front_];
        front_ = (front_ + 1) % capacity_;
        --curr_size_;

        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4 && capacity_ > initial_capacity_) {
            std::size_t newCap = capacity_ / 2;
            if (newCap < initial_capacity_) newCap = initial_capacity_;
            resize(newCap);
        }

        return val;
    }

    T peek() const {
        if (curr_size_ == 0) throw std::runtime_error("Queue empty");
        return array_[front_];
    }

    std::size_t getSize() const {
        return curr_size_;
    }

    std::size_t getMaxCapacity() const {
        return capacity_;
    }
};


