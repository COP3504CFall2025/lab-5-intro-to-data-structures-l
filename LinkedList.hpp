#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

private:
    Node* head;
    Node* tail;
    unsigned int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~LinkedList() { clear(); }

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* current = other.head;
        while (current) {
            addTail(current->data);
            current = current->next;
        }
    }

    LinkedList(LinkedList&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                addTail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = nullptr;
            other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    void addHead(const T& value) {
        Node* node = new Node(value);
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
        ++count;
    }

    void addTail(const T& value) {
        Node* node = new Node(value);
        node->prev = tail;
        if (tail) tail->next = node;
        tail = node;
        if (!head) head = node;
        ++count;
    }

    bool removeHead() {
        if (!head) return false;
        Node* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
        --count;
        return true;
    }

    bool removeTail() {
        if (!tail) return false;
        Node* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
        --count;
        return true;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    unsigned int getCount() const { return count; }
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }

    void printForward() const {
        Node* curr = head;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "\n";
    }

    void printReverse() const {
        Node* curr = tail;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->prev;
        }
        std::cout << "\n";
    }
};
