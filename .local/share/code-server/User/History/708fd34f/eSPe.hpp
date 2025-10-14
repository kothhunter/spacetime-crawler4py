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
        T                       data;
        std::shared_ptr<ListNode> next{nullptr};
        explicit ListNode(const T& v) : data(v) {}
        explicit ListNode(T&&  v)     : data(std::move(v)) {}
    };

public:

    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type*;
        using reference         = value_type&;

        explicit ListIterator(std::shared_ptr<ListNode> p = nullptr) : ptr(p) {}

        ListIterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }
        ListIterator operator++(int) {
            ListIterator tmp(*this);
            ++(*this);
            return tmp;
        }
        reference operator*()  const { return  ptr->data; }
        pointer   operator->() const { return &ptr->data; }

        bool operator==(const ListIterator& rhs) const { return ptr == rhs.ptr; }
        bool operator!=(const ListIterator& rhs) const { return !(*this == rhs); }

    private:
        std::shared_ptr<ListNode> ptr;
    };

    using value_type = T;
    using iterator   = ListIterator;

    SetList() = default;

    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng) {
        std::ranges::for_each(std::forward<Rng>(rng),
                              std::bind_front(&SetList::insert, this));
    }

    iterator begin() { return iterator(head); }
    iterator end()   { return iterator();     }

    bool contains(const T& value) {
        for (auto p = head; p; p = p->next)
            if (p->data == value) return true;
        return false;
    }

    iterator insert(const T& value) {
        if (!head) {                       
            head = std::make_shared<ListNode>(value);
            return iterator(head);
        }
        if (contains(value)) {
            for (auto p = head; p; p = p->next)
                if (p->data == value) return iterator(p);
        }
        auto new_node    = std::make_shared<ListNode>(value);
        new_node->next   = head;
        head             = new_node;
        return iterator(head);
    }

private:
    std::shared_ptr<ListNode> head{nullptr};
};

#endif   