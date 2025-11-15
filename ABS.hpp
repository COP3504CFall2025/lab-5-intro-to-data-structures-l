// ABS.hpp
#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class ABS : public StackInterface<T> {
private:
    T* arr;
    int topIndex;
    int capacity;

public:
    ABS(int cap = 1) : arr(new T[cap]), topIndex(-1), capacity(cap) {}
    ~ABS() { delete[] arr; }

    void push(const T& element) override {
        if (topIndex + 1 >= capacity) throw std::runtime_error("Stack overflow");
        arr[++topIndex] = element;
    }

    T pop() override {
        if (topIndex < 0) throw std::runtime_error("Stack underflow");
        return arr[topIndex--];
    }

    T& peek() override {
        if (topIndex < 0) throw std::runtime_error("Stack is empty");
        return arr[topIndex];
    }

    int getMaxCapacity() const {
        return capacity;
    }

    bool isEmpty() const {
        return topIndex < 0;
    }
};
