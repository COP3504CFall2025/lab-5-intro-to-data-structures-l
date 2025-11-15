// ABQ.hpp
#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABQ : public QueueInterface<T> {
private:
    T* arr;
    int frontIndex;
    int rearIndex;
    int size;
    int capacity;

public:
    ABQ(int cap = 1) : arr(new T[cap]), frontIndex(0), rearIndex(-1), size(0), capacity(cap) {}
    ~ABQ() { delete[] arr; }

    void enqueue(const T& element) override {
        if (size >= capacity) throw std::runtime_error("Queue overflow");
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = element;
        ++size;
    }

    T pop() override {  // This is dequeue
        if (size <= 0) throw std::runtime_error("Queue underflow");
        T value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        --size;
        return value;
    }

    T& peek() override {
        if (size <= 0) throw std::runtime_error("Queue is empty");
        return arr[frontIndex];
    }

    int getMaxCapacity() const {
        return capacity;
    }

    bool isEmpty() const {
        return size == 0;
    }
};
