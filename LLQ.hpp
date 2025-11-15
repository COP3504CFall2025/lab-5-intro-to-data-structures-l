#pragma once
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;

public:
    LLQ() = default;
    LLQ(const LLQ& other) : list(other.list) {}
    LLQ(LLQ&& other) noexcept : list(std::move(other.list)) {}

    LLQ& operator=(const LLQ& other) {
        if (this != &other) list = other.list;
        return *this;
    }

    LLQ& operator=(LLQ&& other) noexcept {
        if (this != &other) list = std::move(other.list);
        return *this;
    }

    void enqueue(const T& item) override {
        list.addTail(item);  // Correct casing
    }

    T dequeue() override {
        if (list.getCount() == 0) throw std::runtime_error("Queue empty");
        T value = list.getHead()->data;
        list.removeHead();   // Correct casing
        return value;
    }

    T& peek() override {
        if (list.getCount() == 0) throw std::runtime_error("Queue empty");
        return list.getHead()->data;
    }

    bool isEmpty() const override {
        return list.getCount() == 0;
    }

    std::size_t getSize() const override {
        return list.getCount();
    }
};
