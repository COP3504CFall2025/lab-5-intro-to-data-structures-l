#ifndef LLS_HPP
#define LLS_HPP

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

template <typename T>
class LLS : public StackInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n=nullptr) : data(d), next(n) {}
    };

    Node* head_;
    std::size_t curr_size_;

    void copyFrom(const LLS& other) {
        if (other.head_ == nullptr) {
            head_ = nullptr;
            curr_size_ = 0;
            return;
        }
        Node* temp = other.head_;
        Node* newHead = new Node(temp->data);
        Node* curr = newHead;
        temp = temp->next;
        while (temp) {
            curr->next = new Node(temp->data);
            curr = curr->next;
            temp = temp->next;
        }
        head_ = newHead;
        curr_size_ = other.curr_size_;
    }

public:
    LLS() : head_(nullptr), curr_size_(0) {}

    LLS(const LLS& other) : head_(nullptr), curr_size_(0) {
        copyFrom(other);
    }

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

    ~LLS() {
        clear();
    }

    void clear() {
        Node* curr = head_;
        while (curr) {
            Node* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
        head_ = nullptr;
        curr_size_ = 0;
    }

    void push(const T& item) override {
        head_ = new Node(item, head_);
        curr_size_++;
    }

    T pop() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        Node* tmp = head_;
        T val = tmp->data;
        head_ = head_->next;
        delete tmp;
        curr_size_--;
        return val;
    }

    T peek() const override {
        if (curr_size_ == 0) throw std::runtime_error("Stack empty");
        return head_->data;
    }

    std::size_t getSize() const override {
        return curr_size_;
    }

    void PrintForward() const override {
        if (!head_) return;
        T* arr = new T[curr_size_];
        Node* curr = head_;
        std::size_t idx = curr_size_;
        while (curr) {
            arr[--idx] = curr->data;
            curr = curr->next;
        }
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::cout << arr[i];
            if (i + 1 < curr_size_) std::cout << " ";
        }
        delete[] arr;
    }

    void PrintReverse() const override {
        Node* curr = head_;
        while (curr) {
            std::cout << curr->data;
            if (curr->next) std::cout << " ";
            curr = curr->next;
        }
    }
};

#endif
