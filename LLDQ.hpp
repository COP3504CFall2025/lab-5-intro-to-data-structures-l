#pragma once
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    LLDQ() = default;

    // Interface methods
    void pushFront(const T& item) override {
        list.addHead(item);
    }

    void pushBack(const T& item) override {
        list.addTail(item);
    }

    void popFront() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        list.removeHead();
    }

    void popBack() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        list.removeTail();
    }

    T& front() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return list.getHead()->data;
    }

    T& back() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return list.getTail()->data;
    }

    bool isEmpty() const override {
        return list.isEmpty();
    }
};
