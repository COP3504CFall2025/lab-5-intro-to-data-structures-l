#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class LLStack : public StackInterface<T> {
private:
    LLDQ<T> dq;

public:
    LLStack() = default;

    void push(const T& item) override {
        dq.pushBack(item); // Stack: push at back (top)
    }

    T pop() override {
        if (dq.getSize() == 0)
            throw std::runtime_error("Stack is empty");
        return dq.popBack(); // Stack: pop from back (top)
    }

    T peek() const override {
        if (dq.getSize() == 0)
            throw std::runtime_error("Stack is empty");
        return dq.back();
    }

    std::size_t getSize() const noexcept override {
        return dq.getSize();
    }

    void clear() {
        dq.clear();
    }
};

template<typename T>
class LLQueue : public QueueInterface<T> {
private:
    LLDQ<T> dq;

public:
    LLQueue() = default;

    void enqueue(const T& item) override {
        dq.pushBack(item); // Queue: enqueue at back
    }

    T dequeue() override {
        if (dq.getSize() == 0)
            throw std::runtime_error("Queue is empty");
        return dq.popFront(); // Queue: dequeue from front
    }

    T peek() const override {
        if (dq.getSize() == 0)
            throw std::runtime_error("Queue is empty");
        return dq.front();
    }

    std::size_t getSize() const noexcept override {
        return dq.getSize();
    }

    void clear() {
        dq.clear();
    }
};

template <typename T>
class DequeInterface {
public:
    virtual void pushFront(const T& item) = 0;
    virtual void pushBack(const T& item) = 0;
    virtual T popFront() = 0;
    virtual T popBack() = 0;
    virtual const T& front() const = 0;
    virtual const T& back() const = 0;
    virtual std::size_t getSize() const noexcept = 0;
    virtual ~DequeInterface() = default;
};
