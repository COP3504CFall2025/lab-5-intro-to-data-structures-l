#pragma once
#include "Interfaces.hpp"
#include <stdexcept>
#include <vector>

template <typename T>
class ABS : public StackInterface<T> {
private:
    std::vector<T> data;

public:
    ABS(std::size_t capacity = 10) {
        data.reserve(capacity);
    }

    void push(const T& element) override {
        data.push_back(element);
    }

    T pop() override {
        if (data.empty()) throw std::runtime_error("Stack is empty");
        T value = data.back();
        data.pop_back();
        return value;
    }

    T peek() const override {
        if (data.empty()) throw std::runtime_error("Stack is empty");
        return data.back();
    }

    std::size_t getSize() const override {
        return data.size();
    }
};
