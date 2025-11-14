#pragma once
#include "LinkedList.hpp"
#include "Interfaces.hpp"

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:

    LLDQ() = default;
    ~LLDQ() = default;
    LLDQ(const LLDQ& other) : list(other.list) {}
    LLDQ& operator=(const LLDQ& other) { list = other.list; return *this; }
    LLDQ(LLDQ&& other) noexcept : list(std::move(other.list)) {}
    LLDQ& operator=(LLDQ&& other) noexcept { list = std::move(other.list); return *this; }

    void pushFront(const T& item) override { list.AddHead(item); }
    void pushBack(const T& item) override { list.AddTail(item); }
    T popFront() override { return list.RemoveHead(); }
    T popBack() override { return list.RemoveTail(); }
    const T& front() const override { return list.getHead()->data; }
    const T& back() const override { return list.getTail()->data; }
    std::size_t getSize() const noexcept override { return list.getCount(); }
};
