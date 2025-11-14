#pragma once
#include "Interfaces.hpp"
#include <vector>
#include <stdexcept>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    std::vector<T> data;

public:
    ABDQ() = default;

    void pushFront(const T& item) override { data.insert(data.begin(), item); }
    void pushBack(const T& item) override { data.push_back(item); }

    void popFront() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        data.erase(data.begin());
    }
    void popBack() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        data.pop_back();
    }

    T& front() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return data.front();
    }
    T& back() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return data.back();
    }

    std::size_t getSize() const override { return data.size(); }
    bool isEmpty() const override { return data.empty(); }
};
