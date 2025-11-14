#pragma once
#include "Interfaces.hpp"
#include <vector>
#include <stdexcept>

template <typename T>
class ABS : public StackInterface<T> {
private:
    std::vector<T> data;

public:
    ABS() = default;

    void push(const T& item) override { data.push_back(item); }

    void pop() override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        data.pop_back();
    }

    T& peek() override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return data.back();
    }

    std::size_t getSize() const override { return data.size(); }
    bool isEmpty() const override { return data.empty(); }
};
