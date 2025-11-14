#pragma once
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;

public:
    LLS() = default;

    void push(const T& item) override {
        list.PushFront(item);
    }

    T pop() override {
        if (list.GetSize() == 0) throw std::runtime_error("Stack is empty");
        T val = list.PeekFront();
        list.PopFront();
        return val;
    }

    T peek() const override {
        if (list.GetSize() == 0) throw std::runtime_error("Stack is empty");
        return list.PeekFront();
    }

    std::size_t getSize() const noexcept override {
        return list.GetSize();
    }

    void clear() {
        list.Clear(); // Fixed capitalization
    }
};
