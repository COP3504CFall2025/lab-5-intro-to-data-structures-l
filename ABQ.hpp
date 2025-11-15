#pragma once
#include "Interfaces.hpp"
#include <stdexcept>
#include <vector>

template <typename T>
class ABQ : public QueueInterface<T> {
private:
    std::vector<T> data;
    std::size_t frontIndex;
    std::size_t size;
    std::size_t capacity;

public:
    ABQ(std::size_t cap = 10) : data(cap), frontIndex(0), size(0), capacity(cap) {}

    void enqueue(const T& element) {
        if (size == capacity) throw std::runtime_error("Queue overflow");
        std::size_t idx = (frontIndex + size) % capacity;
        data[idx] = element;
        size++;
    }

    T dequeue() override {  // required by interface
        if (size == 0) throw std::runtime_error("Queue underflow");
        T value = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        size--;
        return value;
    }

    T peek() const {
        if (size == 0) throw std::runtime_error("Queue is empty");
        return data[frontIndex];
    }

    std::size_t getSize() const override {
        return size;
    }
};
