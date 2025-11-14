#pragma once
#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>

template <typename T>
class LLDeque : public DequeInterface<T> {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& item) : data(item), prev(nullptr), next(nullptr) {}
    };
    Node* front_;
    Node* back_;
    std::size_t size_;

public:
    LLDeque() : front_(nullptr), back_(nullptr), size_(0) {}
    ~LLDeque() {
        while (front_) {
            Node* tmp = front_;
            front_ = front_->next;
            delete tmp;
        }
    }

    void pushFront(const T& item) override {
        Node* n = new Node(item);
        n->next = front_;
        if (front_) front_->prev = n;
        front_ = n;
        if (!back_) back_ = n;
        ++size_;
    }

    void pushBack(const T& item) override {
        Node* n = new Node(item);
        n->prev = back_;
        if (back_) back_->next = n;
        back_ = n;
        if (!front_) front_ = n;
        ++size_;
    }

    T popFront() override {
        if (!front_) throw std::runtime_error("Deque is empty");
        Node* tmp = front_;
        T val = tmp->data;
        front_ = front_->next;
        if (front_) front_->prev = nullptr;
        else back_ = nullptr;
        delete tmp;
        --size_;
        return val;
    }

    T popBack() override {
        if (!back_) throw std::runtime_error("Deque is empty");
        Node* tmp = back_;
        T val = tmp->data;
        back_ = back_->prev;
        if (back_) back_->next = nullptr;
        else front_ = nullptr;
        delete tmp;
        --size_;
        return val;
    }

    const T& front() const override {
        if (!front_) throw std::runtime_error("Deque is empty");
        return front_->data;
    }

    const T& back() const override {
        if (!back_) throw std::runtime_error("Deque is empty");
        return back_->data;
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }
};
