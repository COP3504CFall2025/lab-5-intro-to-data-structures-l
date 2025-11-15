// LLS.hpp
#pragma once
#include "Interfaces.hpp"
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };
    Node* head;
    int capacity;

public:
    LLS(int cap = 1) : head(nullptr), capacity(cap) {}
    ~LLS() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void push(const T& element) override {
        head = new Node(element, head);
    }

    T pop() override {
        if (!head) throw std::runtime_error("Stack is empty");
        Node* tmp = head;
        T value = tmp->data;
        head = head->next;
        delete tmp;
        return value;
    }

    T& peek() override {
        if (!head) throw std::runtime_error("Stack is empty");
        return head->data;
    }

    int getMaxCapacity() const {
        return capacity;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};
