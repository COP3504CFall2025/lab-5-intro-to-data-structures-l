#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

template <typename T>
class LLS : public StackInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head_;
    std::size_t curr_size_;

    void copyFrom(const LLS& other) {
        if (!other.head_) {
            head_ = nullptr;
            curr_size_ = 0;
            return;
        }
        Node* temp = other.head_;
        head_ = new Node(temp->data);
        Node* curr = head_;
        temp = temp->next;
        while (temp) {
            curr->next = new Node(temp->data);
            curr = curr->next;
            temp = temp->next;
        }
        curr_size_ = other.curr_size_;
    }

public:
    LLS() : head_(nullptr), curr_size_(0) {}

    LLS(const LLS& other) : head_(nullptr), curr_size_(0) { copyFrom(other); }

    LLS(LLS&& other) noexcept : head_(other.head_), curr_size_(other.curr_size_) {
        other.head_ = nullptr;
        other.curr_size_ = 0;
    }

    LLS& operator=(const LLS& other) {
        if (this == &other) return *this;
        clear();
        copyFrom(other);
        return *this;
    }

    LLS& operator=(LLS&& other) noexcept {
        if (this == &other) return *this;
        clear();
        head_ = other.head_;
        curr_size_ = other.curr_size_;
        other.head_ = nullptr;
        other.curr_size_ = 0;
        return *this;
    }

    ~LLS() { clear(); }

    void clear() {
        while (head_) {
            Node* tmp = head_->next;
            delete head_;
            head_ = tmp;
        }
        curr_size_ = 0;
    }

    void push(const T& item) {
        head_ = new Node(item, head_);
        curr_size_++;
    }

    T pop() {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        Node* tmp = head_;
        T val = tmp->data;
        head_ = head_->next;
        delete tmp;
        curr_size_--;
        return val;
    }

    T& peek() {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        return head_->data;
    }

    std::size_t getSize() const { return curr_size_; }
    bool isEmpty() const { return curr_size_ == 0; }

    // Optional helper functions
    std::size_t getMaxCapacity() const { return SIZE_MAX; }
    void PrintForward() const {
        T* arr = new T[curr_size_];
        Node* curr = head_;
        std::size_t idx = curr_size_;
        while (curr) {
            arr[--idx] = curr->data;
            curr = curr->next;
        }
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::cout << arr[i] << (i + 1 < curr_size_ ? " " : "");
        }
        delete[] arr;
    }

    void PrintReverse() const {
        Node* curr = head_;
        while (curr) {
            std::cout << curr->data;
            if (curr->next) std::cout << " ";
            curr = curr->next;
        }
    }
};


