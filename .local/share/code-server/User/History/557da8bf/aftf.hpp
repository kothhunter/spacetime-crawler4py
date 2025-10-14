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
        
        auto newNode = std::make_shared<ListNode>(ListNode{value, head});
        head = newNode;
        return iterator(newNode);
    }

private:
    std::shared_ptr<ListNode> head = nullptr;
};

#endif // SET_LIST_HPP

#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class MapArray {
public:
    class ArrayIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ArrayIterator(pointer ptr = nullptr) : ptr(ptr) {}

        ArrayIterator& operator++() { ++ptr; return *this; }
        ArrayIterator& operator--() { --ptr; return *this; }
        ArrayIterator operator++(int) { ArrayIterator temp = *this; ++(*this); return temp; }
        ArrayIterator operator--(int) { ArrayIterator temp = *this; --(*this); return temp; }
        ArrayIterator& operator+=(difference_type d) { ptr += d; return *this; }
        ArrayIterator& operator-=(difference_type d) { ptr -= d; return *this; }
        friend ArrayIterator operator+(ArrayIterator it, difference_type d) { return it += d; }
        friend ArrayIterator operator+(difference_type d, ArrayIterator it) { return it += d; }
        friend ArrayIterator operator-(ArrayIterator it, difference_type d) { return it -= d; }
        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs) { return lhs.ptr - rhs.ptr; }
        auto operator<=>(const ArrayIterator& other) const = default;
        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }
        reference operator[](difference_type d) const { return *(ptr + d); }
    
    private:
        pointer ptr;
    };

    using value_type = std::pair<Key, Value>;
    using iterator = ArrayIterator;

    iterator begin() { return iterator(data.data()); }
    iterator end() { return iterator(data.data() + data.size()); }

    Value& operator[](const Key& key) {
        auto it = std::lower_bound(data.begin(), data.end(), key,
                                   [](const value_type& lhs, const Key& rhs) { return lhs.first < rhs; });
        if (it == data.end() || it->first != key) {
            it = data.insert(it, {key, Value{}});
        }
        return it->second;
    }

private:
    std::vector<std::pair<Key, Value>> data;
};

#endif // MAP_ARRAY_HPP
