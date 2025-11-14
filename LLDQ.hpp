#pragma once
#include "Interfaces.hpp"

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    std::size_t size;

public:
    LLDQ() : head(nullptr), tail(nullptr), size(0) {}
    ~LLDQ() { while (!isEmpty()) popFront(); }

    void pushFront(const T& item) override {
        Node* newNode = new Node(item);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
        ++size;
    }

    void pushBack(const T& item) override {
        Node* newNode = new Node(item);
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = tail;
        ++size;
    }

    void popFront() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        --size;
    }

    void popBack() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        --size;
    }

    T& front() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return head->data;
    }

    T& back() override {
        if (isEmpty()) throw std::runtime_error("Deque is empty");
        return tail->data;
    }

    std::size_t getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
};
