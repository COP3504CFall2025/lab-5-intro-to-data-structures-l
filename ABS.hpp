#pragma once
#include <stdexcept>
#include <cstddef>

template <typename T>
class ABS {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t initial_capacity_;
    std::size_t curr_size_;

    void resize(std::size_t new_capacity) {
        T* new_array = new T[new_capacity];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
        capacity_ = new_capacity;
    }

public:
    // Default constructor
    ABS() : capacity_(1), initial_capacity_(1), curr_size_(0) {
        array_ = new T[capacity_];
    }

    // Constructor with initial capacity
    ABS(std::size_t initialCapacity)
        : capacity_(initialCapacity), initial_capacity_(initialCapacity), curr_size_(0) {
        if (capacity_ == 0) capacity_ = initial_capacity_ = 1;
        array_ = new T[capacity_];
    }

    // Copy constructor
    ABS(const ABS& other)
        : capacity_(other.capacity_), initial_capacity_(other.initial_capacity_),
          curr_size_(other.curr_size_) {
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            array_[i] = other.array_[i];
        }
    }

    // Move constructor
    ABS(ABS&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_),
          initial_capacity_(other.initial_capacity_), curr_size_(other.curr_size_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    // Copy assignment
    ABS& operator=(const ABS& other) {
        if (this != &other) {
            delete[] array_;
            capacity_ = other.capacity_;
            initial_capacity_ = other.initial_capacity_;
            curr_size_ = other.curr_size_;
            array_ = new T[capacity_];
            for (std::size_t i = 0; i < curr_size_; ++i) {
                array_[i] = other.array_[i];
            }
        }
        return *this;
    }

    // Move assignment
    ABS& operator=(ABS&& other) noexcept {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            capacity_ = other.capacity_;
            initial_capacity_ = other.initial_capacity_;
            curr_size_ = other.curr_size_;
            other.array_ = nullptr;
            other.capacity_ = 0;
            other.curr_size_ = 0;
        }
        return *this;
    }

    ~ABS() { delete[] array_; }

    void push(const T& value) {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[curr_size_++] = value;
    }

    T pop() {
        if (curr_size_ == 0) throw std::runtime_error("Stack is empty");
        --curr_size_;
        T value = array_[curr_size_];
        if (curr_size_ <= capacity_ / 4 && capacity_ / 2 >= initial_capacity_)
            resize(capacity_ / 2);
        return value;
    }

    T peek() const {
        if (curr_size_ == 0) throw std::runtime_error("Stack is empty");
        return array_[curr_size_ - 1];
    }

    std::size_t size() const { return curr_size_; }
    std::size_t getMaxCapacity() const { return capacity_; }
};
