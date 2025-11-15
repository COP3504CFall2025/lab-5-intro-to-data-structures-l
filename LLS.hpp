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
    std::size_t currentSize;

public:
    LLS() : head(nullptr), currentSize(0) {}
    ~LLS() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void push(const T& element) override {
        head = new Node(element, head);
        currentSize++;
    }

    T pop() override {
        if (!head) throw std::runtime_error("Stack is empty");
        Node* tmp = head;
        T value = tmp->data;
        head = head->next;
        delete tmp;
        currentSize--;
        return value;
    }

    T peek() const override {
        if (!head) throw std::runtime_error("Stack is empty");
        return head->data;
    }

    std::size_t getSize() const override {
        return currentSize;
    }
};
