#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

public:

    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}


    ~LinkedList() {
        Clear();
    }


    LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
        Node* curr = other.head_;
        while (curr) {
            AddBack(curr->data);
            curr = curr->next;
        }
    }


    LinkedList(LinkedList&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }


    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            Clear();
            Node* curr = other.head_;
            while (curr) {
                AddBack(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }


    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            Clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }


    void AddFront(const T& value) {
        Node* node = new Node(value);
        node->next = head_;
        if (head_) head_->prev = node;
        head_ = node;
        if (!tail_) tail_ = node;
        ++size_;
    }
    void AddBack(const T& value) {
        Node* node = new Node(value);
        node->prev = tail_;
        if (tail_) tail_->next = node;
        tail_ = node;
        if (!head_) head_ = node;
        ++size_;
    }


    void RemoveFront() {
        if (!head_) throw std::runtime_error("List is empty");
        Node* tmp = head_;
        head_ = head_->next;
        if (head_) head_->prev = nullptr;
        else tail_ = nullptr;
        delete tmp;
        --size_;
    }


    void RemoveBack() {
        if (!tail_) throw std::runtime_error("List is empty");
        Node* tmp = tail_;
        tail_ = tail_->prev;
        if (tail_) tail_->next = nullptr;
        else head_ = nullptr;
        delete tmp;
        --size_;
    }


    T& Front() {
        if (!head_) throw std::runtime_error("List is empty");
        return head_->data;
    }


    T& Back() {
        if (!tail_) throw std::runtime_error("List is empty");
        return tail_->data;
    }


    void Clear() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }


    std::size_t Size() const { return size_; }


    bool IsEmpty() const { return size_ == 0; }
};
