#pragma once
#include "Interfaces.hpp"

template <typename T>
class LLS : public StackInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };
    Node* head;
    std::size_t size;

public:
    LLS() : head(nullptr), size(0) {}
    ~LLS() { while (!isEmpty()) pop(); }

    void push(const T& item) override {
        head = new Node(item, head);
        ++size;
    }

    void pop() override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        Node* temp = head;
        head = head->next;
        delete temp;
        --size;
    }

    T& peek() override {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return head->data;
    }

    std::size_t getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
};
