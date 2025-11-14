#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };

    // Behaviors
    void printForward() const;
    void printReverse() const;

    // Accessors
    [[nodiscard]] unsigned int getCount() const;
    Node* getHead();
    const Node* getHead() const;
    Node* getTail();
    const Node* getTail() const;

    // Insertion
    void addHead(const T& data);
    void addTail(const T& data);

    // Removal
    bool removeHead();
    bool removeTail();
    void Clear();

    // Operators
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    // Construction/Destruction
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    LinkedList(LinkedList<T>&& other) noexcept;
    ~LinkedList();

private:
    Node* head;
    Node* tail;
    unsigned int count;
};


template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
    : head(nullptr), tail(nullptr), count(0)
{
    Node* curr = list.head;
    while (curr) {
        addTail(curr->data);
        curr = curr->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
    : head(other.head), tail(other.tail), count(other.count)
{
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}


template <typename T>
void LinkedList<T>::printForward() const {
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " ";
        curr = curr->next;
    }
    cout << endl;
}

template <typename T>
void LinkedList<T>::printReverse() const {
    Node* curr = tail;
    while (curr) {
        cout << curr->data;
        if (curr->prev) cout << " ";
        curr = curr->prev;
    }
    cout << endl;
}


template <typename T>
unsigned int LinkedList<T>::getCount() const {
    return count;
}

template <typename T>
 LinkedList<T>::Node* LinkedList<T>::getHead() {
    return head;
}

template <typename T>
const LinkedList<T>::Node* LinkedList<T>::getHead() const {
    return head;
}

template <typename T>
 LinkedList<T>::Node* LinkedList<T>::getTail() {
    return tail;
}

template <typename T>
const LinkedList<T>::Node* LinkedList<T>::getTail() const {
    return tail;
}


template <typename T>
void LinkedList<T>::addHead(const T& data) {
    Node* node = new Node(data);
    node->next = head;

    if (head)
        head->prev = node;
    else
        tail = node;

    head = node;
    count++;
}

template <typename T>
void LinkedList<T>::addTail(const T& data) {
    Node* node = new Node(data);
    node->prev = tail;

    if (tail)
        tail->next = node;
    else
        head = node;

    tail = node;
    count++;
}


template <typename T>
bool LinkedList<T>::removeHead() {
    if (!head) return false;

    Node* temp = head;
    head = head->next;

    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;

    delete temp;
    count--;
    return true;
}

template <typename T>
bool LinkedList<T>::removeTail() {
    if (!tail) return false;

    Node* temp = tail;
    tail = tail->prev;

    if (tail)
        tail->next = nullptr;
    else
        head = nullptr;

    delete temp;
    count--;
    return true;
}

template <typename T>
void LinkedList<T>::Clear() {
    while (head)
        removeHead();
}

explicit ABDQ(std::size_t capacity)
    : data_(new T[capacity > 0 ? capacity : 1]),
      capacity_(capacity > 0 ? capacity : 1),
      size_(0),
      front_(0),
      back_(0) {}
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this == &other) return *this;

    Clear();

    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;

    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this == &rhs) return *this;

    Clear();

    Node* curr = rhs.head;
    while (curr) {
        addTail(curr->data);
        curr = curr->next;
    }

    return *this;
}
