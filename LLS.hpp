#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLS() : list() {}

    // Push item onto the stack
    void push(const T& item) override {
        // Insert at head for LIFO behavior
        list.addHead(item);
    }

    // Remove and return the top item
    T pop() override {
        auto headNode = list.getHead();
        if (!headNode)
            throw std::out_of_range("Stack is empty");

        T value = headNode->data;
        list.removeHead();
        return value;
    }

    // Return the top item without removing
    T peek() const override {
        auto headNode = list.getHead();
        if (!headNode)
            throw std::out_of_range("Stack is empty");

        return headNode->data;
    }

    // Get the number of items in the stack
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};
