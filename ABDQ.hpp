#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data;
    std::size_t capacity;
    std::size_t size;
    std::size_t frontIndex;

    void resize() {
        std::size_t newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size; ++i)
            newData[i] = data[(frontIndex + i) % capacity];
        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
    }

public:
    ABDQ() : data(new T[4]), capacity(4), size(0), frontIndex(0) {}
    ~ABDQ() { delete[] data; }

    void pushFront(const T& item) override {
        if (size == capacity) resize();
        frontIndex = (frontIndex == 0) ? capacity - 1 : frontIndex - 1;
        data[frontIndex] = item;
        ++size;
    }

    void pushBack(const T& item) override {
        if (size == capacity) resize();
        data[(frontIndex + size) % capacity] = item;
        ++size;
    }

    void popFront() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        frontIndex = (frontIndex + 1) % capacity;
        --size;
    }

    void popBack() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        --size;
    }

    T& front() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return data[frontIndex];
    }

    T& back() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return data[(frontIndex + size - 1) % capacity];
    }

    std::size_t getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
};
