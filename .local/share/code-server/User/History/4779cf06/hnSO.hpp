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
        // Iterator traits:
        using iterator_category = ???;
        using value_type = ???;
        using difference_type = ???;
        using pointer = ???;
        using reference = ???;

        explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr);

        ArrayIterator& operator++();
        ArrayIterator& operator--();
        ArrayIterator operator++(int);
        ArrayIterator operator--(int);
        ArrayIterator& operator+=(difference_type d);
        ArrayIterator& operator-=(difference_type d);
        friend ArrayIterator operator+(ArrayIterator it, difference_type d);
        friend ArrayIterator operator+(difference_type d, ArrayIterator it);
        friend ArrayIterator operator-(ArrayIterator it, difference_type d);
        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs);
        auto operator<=>(const ArrayIterator& other) const = default;
        std::pair<Key, Value>& operator*() const;
        std::pair<Key, Value>* operator->() const;
        std::pair<Key, Value>& operator[](difference_type d) const;

    private:
        std::pair<Key, Value>* ptr;
    };

    using value_type = std::pair<Key, Value>;
    using iterator = ArrayIterator;
    // Normally there would also be a const_iterator

    ArrayIterator begin();
    ArrayIterator end();
    Value& operator[](const Key& key);

private:
    std::vector<std::pair<Key, Value>> data;
};

#endif // MAP_ARRAY_HPP

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
