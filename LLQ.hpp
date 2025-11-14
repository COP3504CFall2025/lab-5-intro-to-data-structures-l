#pragma once
#include "Interfaces.hpp"

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };
    Node* head;
    Node* tail;
    std::size_t size;

public:
    LLQ() : head(nullptr), tail(nullptr), size(0) {}
    ~LLQ() { while (!isEmpty()) dequeue(); }

    void enqueue(const T& item) override {
        Node* newNode = new Node(item);
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = tail;
        ++size;
    }

    void dequeue() override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        --size;
    }

    T& peek() override {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return head->data;
    }

    std::size_t getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
};
