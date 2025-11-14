#pragma once
#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>

template <typename T>
class LLStack : public StackInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& item, Node* n = nullptr) : data(item), next(n) {}
    };
    Node* head_;
    std::size_t size_;

public:
    LLStack() : head_(nullptr), size_(0) {}
    ~LLStack() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
    }

    void push(const T& item) override {
        head_ = new Node(item, head_);
        ++size_;
    }

    T pop() override {
        if (!head_) throw std::runtime_error("Stack is empty");
        Node* tmp = head_;
        T val = head_->data;
        head_ = head_->next;
        delete tmp;
        --size_;
        return val;
    }

    T peek() const override {
        if (!head_) throw std::runtime_error("Stack is empty");
        return head_->data;
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }
};
