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
    using value_type = std::pair<Key, Value>;
    class ArrayIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = MapArray::value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ArrayIterator(pointer ptr = nullptr) : ptr(ptr) {}

        ArrayIterator& operator++() {
            ++ptr;
            return *this;
        }
        
        ArrayIterator& operator--() { 
            --ptr; 
            return *this; 
        }

        ArrayIterator operator++(int) { 
            ArrayIterator temp = *this; 
            ++ptr; 
            return temp; 
        }

        ArrayIterator operator--(int) { 
            ArrayIterator temp = *this; 
            --ptr; 
            return temp; 
        }

        ArrayIterator& operator+=(difference_type d) {
            ptr += d;
            return *this;
        }

        ArrayIterator& operator-=(difference_type d) {
            ptr -= d;
            return *this;
        }

        reference operator*() const { 
            return *ptr; 
        }

        pointer operator->() const { 
            return ptr; 
        }

        reference operator[](difference_type d) const { 
            return *(ptr + d); 
        }

        friend ArrayIterator operator+(ArrayIterator it, difference_type d) { 
            return ArrayIterator(it.ptr + d); 
        }

        friend ArrayIterator operator+(difference_type d, ArrayIterator it) { 
            return ArrayIterator(it.ptr + d); 
        }

        friend ArrayIterator operator-(ArrayIterator it, difference_type d) { 
            return ArrayIterator(it.ptr - d); 
        }

        friend difference_type operator-(const ArrayIterator& lhs, const ArrayIterator& rhs) { 
            return lhs.ptr - rhs.ptr; 
        }

        bool operator==(const ArrayIterator& other) const { 
            return ptr == other.ptr; 
        }

        bool operator!=(const ArrayIterator& other) const { 
            return ptr != other.ptr; 
        }

        bool operator<(const ArrayIterator& other) const { 
            return ptr < other.ptr; 
        }

        bool operator>(const ArrayIterator& other) const { 
            return ptr > other.ptr; 
        }

        bool operator<=(const ArrayIterator& other) const { 
            return ptr <= other.ptr; 
        }

        bool operator>=(const ArrayIterator& other) const { 
            return ptr >= other.ptr; 
        }

    private:
        pointer ptr;
    };

    ArrayIterator begin() { 
        return ArrayIterator(data.data()); 
    }

    ArrayIterator end() { 
        return ArrayIterator(data.data() + data.size()); 
    }

    Value& operator[](const Key& key) {
    auto it = std::lower_bound(data.begin(), data.end(), std::make_pair(key, Value()),
                               [](const auto& pair, const auto& val) { return pair.first < val.first; });

    if (it != data.end() && it->first == key) {
        return it->second;
    } else {
        return data.emplace(it, key, Value())->second;
    }
}

private:
    std::vector<value_type> data;
};

#endif