#pragma once
#include <stdexcept>
#include <cstddef>

template <typename T>
class ABQ {
private:
    T* array_;
    std::size_t capacity_;
    std::size_t initial_capacity_;
    std::size_t front_;
    std::size_t rear_;
    std::size_t curr_size_;

    void resize(std::size_t new_capacity) {
        T* new_array = new T[new_capacity];
        for (std::size_t i = 0; i < curr_size_; ++i) {
            new_array[i] = array_[(front_ + i) % capacity_];
        }
        delete[] array_;
        array_ = new_array;
        capacity_ = new_capacity;
        front_ = 0;
        rear_ = curr_size_;
    }

public:
    ABQ() : capacity_(1), initial_capacity_(1), front_(0), rear_(0), curr_size_(0) {
        array_ = new T[capacity_];
    }

    ABQ(std::size_t initialCapacity)
        : capacity_(initialCapacity), initial_capacity_(initialCapacity),
          front_(0), rear_(0), curr_size_(0) {
        if (capacity_ == 0) capacity_ = initial_capacity_ = 1;
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

    ABQ& operator=(const ABQ& other) {
        if (this != &other) {
            delete[] array_;
            capacity_ = other.capacity_;
            initial_capacity_ = other.initial_capacity_;
            front_ = other.front_;
            rear_ = other.rear_;
            curr_size_ = other.curr_size_;
            array_ = new T[capacity_];
            for (std::size_t i = 0; i < curr_size_; ++i) {
                array_[(front_ + i) % capacity_] = other.array_[(front_ + i) % capacity_];
            }
        }
        return *this;
    }

    ABQ& operator=(ABQ&& other) noexcept {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            capacity_ = other.capacity_;
            initial_capacity_ = other.initial_capacity_;
            front_ = other.front_;
            rear_ = other.rear_;
            curr_size_ = other.curr_size_;
            other.array_ = nullptr;
            other.capacity_ = 0;
            other.curr_size_ = 0;
        }
        return *this;
    }

    ~ABQ() { delete[] array_; }

    void enqueue(const T& value) {
        if (curr_size_ == capacity_) resize(capacity_ * 2);
        array_[rear_] = value;
        rear_ = (rear_ + 1) % capacity_;
        ++curr_size_;
    }

    T dequeue() {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        T value = array_[front_];
        front_ = (front_ + 1) % capacity_;
        --curr_size_;
        if (curr_size_ <= capacity_ / 4 && capacity_ / 2 >= initial_capacity_)
            resize(capacity_ / 2);
        return value;
    }

    T peek() const {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        return array_[front_];
    }

    std::size_t getMaxCapacity() const { return capacity_; }

    // ✅ Add this to pass the test
    std::size_t getSize() const { return curr_size_; }
};
