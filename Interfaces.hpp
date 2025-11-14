#pragma once
#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
public:
    virtual ~StackInterface() = default;
    virtual void push(const T& item) = 0;
    virtual void pop() = 0;
    virtual T& peek() = 0;
    virtual std::size_t getSize() const = 0;
    virtual bool isEmpty() const = 0;
};


template <typename T>
class QueueInterface {
public:
    virtual ~QueueInterface() = default;
    virtual void enqueue(const T& item) = 0;
    virtual void dequeue() = 0;
    virtual T& peek() = 0;
    virtual std::size_t getSize() const = 0;
    virtual bool isEmpty() const = 0;
};


template <typename T>
class DequeInterface {
public:
    virtual ~DequeInterface() = default;
    virtual void pushFront(const T& item) = 0;
    virtual void pushBack(const T& item) = 0;
    virtual void popFront() = 0;
    virtual void popBack() = 0;
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual std::size_t getSize() const = 0;
    virtual bool isEmpty() const = 0;
};
