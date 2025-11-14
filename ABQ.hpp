#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABQ : public QueueInterface<T> {
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
    ABQ() : data(new T[4]), capacity(4), size(0), frontIndex(0) {}
    ~ABQ() { delete[] data; }

    void enqueue(const T& item) override {
        if (size == capacity) resize();
        data[(frontIndex + size) % capacity] = item;
        ++size;
    }

    void dequeue() override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        frontIndex = (frontIndex + 1) % capacity;
        --size;
    }

    T& peek() override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return data[frontIndex];
    }

    std::size_t getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
};
