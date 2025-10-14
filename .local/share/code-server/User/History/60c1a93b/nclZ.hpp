#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <iosfwd>
#include "shape.hpp"

class Picture {
public:
    Picture();

    Picture(const Picture& other);
    Picture(Picture&& other);

    void swap(Picture& other);

    Picture& operator=(const Picture& other);
    Picture& operator=(Picture&& other);

    void add(const Shape& shape);

    void print_all(std::ostream& out) const;

    void draw_all(std::ostream& out) const;

    // Returns the sum of the areas of all the Shapes in this Picture
    double total_area() const;

    // Frees all storage owned by this Picture when it dies
    ~Picture();

private:
    struct ListNode {
        Shape* shape; // The data in this ListNode
        ListNode* next; // Pointer to next ListNode
    };

    ListNode* head; // Pointer to the head of our linked list
    ListNode* tail; // Pointer to the tail of our linked list
};

#endif