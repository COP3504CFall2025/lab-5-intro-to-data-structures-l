#pragma once
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Big Five
    LLDQ() = default;
    ~LLDQ() = default;
    LLDQ(const LLDQ& other) : list(other.list) {}
    LLDQ& operator=(const LLDQ& other) { list = other.list; return *this; }
    LLDQ(LLDQ&& other) noexcept : list(std::move(other.list)) {}
    LLDQ& operator=(LLDQ&& other) noexcept { list = std::move(other.list); return *this; }

    void pushFront(const T& item) override { list.addHead(item); }
    void pushBack(const T& item) override { list.addTail(item); }

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

    bool isEmpty() const override { return list.getCount() == 0; }

    std::size_t getSize() const noexcept override { return list.getCount(); }
};
