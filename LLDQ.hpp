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

    LLDQ(const LLDQ& other) : list(other.list) {}

    LLDQ(LLDQ&& other) noexcept : list(std::move(other.list)) {}

    LLDQ& operator=(const LLDQ& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    LLDQ& operator=(LLDQ&& other) noexcept {
        if (this != &other) {
            list = std::move(other.list);
        }
        return *this;
    }

    void pushFront(const T& item) override {
        list.AddHead(item);
    }

    void pushBack(const T& item) override {
        list.AddTail(item);
    }

    T popFront() override {
        if (list.isEmpty()) throw std::runtime_error("Deque empty");
        T value = list.getHead()->data;
        list.RemoveHead();
        return value;
    }

    T popBack() override {
        if (list.isEmpty()) throw std::runtime_error("Deque empty");
        T value = list.getTail()->data;
        list.RemoveTail();
        return value;
    }

    T& front() override {
        if (list.isEmpty()) throw std::runtime_error("Deque empty");
        return list.getHead()->data;
    }

    T& back() override {
        if (list.isEmpty()) throw std::runtime_error("Deque empty");
        return list.getTail()->data;
    }

    std::size_t getSize() const override {
        return list.getCount();
    }

    bool isEmpty() const override {
        return list.isEmpty();
    }
};
