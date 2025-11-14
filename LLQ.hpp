#pragma once
#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>

template <typename T>
class LLQueue : public QueueInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& item) : data(item), next(nullptr) {}
    };
    Node* front_;
    Node* back_;
    std::size_t size_;

public:
    LLQueue() : front_(nullptr), back_(nullptr), size_(0) {}
    ~LLQueue() {
        while (front_) {
            Node* tmp = front_;
            front_ = front_->next;
            delete tmp;
        }
    }

    void enqueue(const T& item) override {
        Node* n = new Node(item);
        if (!back_) {
            front_ = back_ = n;
        } else {
            back_->next = n;
            back_ = n;
        }
        ++size_;
    }

    T dequeue() override {
        if (!front_) throw std::runtime_error("Queue is empty");
        Node* tmp = front_;
        T val = front_->data;
        front_ = front_->next;
        if (!front_) back_ = nullptr;
        delete tmp;
        --size_;
        return val;
    }

    T peek() const override {
        if (!front_) throw std::runtime_error("Queue is empty");
        return front_->data;
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }
};
