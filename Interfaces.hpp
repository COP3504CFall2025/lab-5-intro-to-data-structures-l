#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    void push(const T& item);
    T pop();
    T peek() const;
    std::size_t getSize() const noexcept;
};


template <typename T>
class QueueInterface {
    void enqueue(const T& item);
    T dequeue();
    T peek() const;
    std::size_t getSize() const noexcept;
};


template <typename T>
class DequeInterface {
    void pushFront(const T& item);
    void pushBack(const T& item);
    T popFront();
    T popBack();
    const T& front() const;
    const T& back() const;
    std::size_t getSize() const noexcept;
};

