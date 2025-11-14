#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* data;
    std::size_t capacity;
    std::size_t size;

    void resize() {
        std::size_t newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    ABS() : data(new T[4]), capacity(4), size(0) {}
    ~ABS() { delete[] data; }

    void push(const T& item) override {
        if (size == capacity) resize();
        data[size++] = item;
    }

    void pop() override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        --size;
    }

    T& peek() override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return data[size - 1];
    }

    std::size_t getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
};
