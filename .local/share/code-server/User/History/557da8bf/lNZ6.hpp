#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList {
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;
    };

public:
    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr) : ptr(ptr) {}

        ListIterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator temp = *this;
            ++(*this);
            return temp;
        }

        reference operator*() const { return ptr->data; }
        pointer operator->() const { return &(ptr->data); }

        bool operator==(const ListIterator& other) const { return ptr == other.ptr; }
    
    private:
        std::shared_ptr<ListNode> ptr;
    };

    using value_type = T;
    using iterator = ListIterator;

    SetList() = default;

    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng) {
        std::ranges::for_each(std::forward<Rng>(rng),
                              std::bind_front(&SetList::insert, this));
    }

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    bool contains(const T& value) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == value) return true;
        }
        return false;
    }

    iterator insert(T value) {
        if (contains(value)) return end();
        
        auto newNode = std::make_shared<ListNode>(ListNode{std::move(value), head});
        head = newNode;
        return iterator(newNode);
    }
    iterator insert(T value) {
    if (contains(value)) return end();

    // Use std::make_shared with std::move to avoid unnecessary copies
    auto newNode = std::make_shared<ListNode>(ListNode{std::move(value), head});
    head = newNode;

    return iterator(newNode);
}

private:
    std::shared_ptr<ListNode> head = nullptr;
};

#endif