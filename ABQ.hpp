#pragma once
#include "Interfaces.hpp"
#include <vector>
#include <stdexcept>

template <typename T>
class ABQ : public QueueInterface<T> {
private:
    std::vector<T> data;

public:
    ABQ() = default;

    void enqueue(const T& item) override { data.push_back(item); }

    void dequeue() override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        data.erase(data.begin());
    }

    T& peek() override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return data.front();
    }

    std::size_t getSize() const override { return data.size(); }
    bool isEmpty() const override { return data.empty(); }
};
