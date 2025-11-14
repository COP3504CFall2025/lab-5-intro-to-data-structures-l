#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template<typename T>
class LLDQ : public DequeInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

public:
    LLDQ() : head_(nullptr), tail_(nullptr), size_(0) {}

    LLDQ(const LLDQ& other) : head_(nullptr), tail_(nullptr), size_(0) {
        Node* curr = other.head_;
        while (curr) {
            pushBack(curr->data);
            curr = curr->next;
        }
    }

    LLDQ(LLDQ&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    LLDQ& operator=(const LLDQ& other) {
        if (this != &other) {
            clear();
            Node* curr = other.head_;
            while (curr) {
                pushBack(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    LLDQ& operator=(LLDQ&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~LLDQ() { clear(); }

    void pushFront(const T& item) override {
        Node* node = new Node(item);
        node->next = head_;
        if (head_) head_->prev = node;
        head_ = node;
        if (!tail_) tail_ = node;
        ++size_;
    }

    void pushBack(const T& item) override {
        Node* node = new Node(item);
        node->prev = tail_;
        if (tail_) tail_->next = node;
        tail_ = node;
        if (!head_) head_ = node;
        ++size_;
    }

    T popFront() override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        Node* node = head_;
        T value = node->data;
        head_ = head_->next;
        if (head_) head_->prev = nullptr;
        else tail_ = nullptr;
        delete node;
        --size_;
        return value;
    }

    T popBack() override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        Node* node = tail_;
        T value = node->data;
        tail_ = tail_->prev;
        if (tail_) tail_->next = nullptr;
        else head_ = nullptr;
        delete node;
        --size_;
        return value;
    }

    const T& front() const override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        return head_->data;
    }

    const T& back() const override {
        if (size_ == 0) throw std::runtime_error("Deque is empty");
        return tail_->data;
    }

    std::size_t getSize() const noexcept override {
        return size_;
    }

    void clear() {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
        tail_ = nullptr;
        size_ = 0;
    }
};
