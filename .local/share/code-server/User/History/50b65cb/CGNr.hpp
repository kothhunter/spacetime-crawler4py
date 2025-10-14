// class Picture
#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <iosfwd>
#include "shape.hpp"

class Picture {
public:
    // Initializing constructor creates this as an empty picture
    Picture();

    // Copy and move constructors for Picture
    Picture(const Picture& other);
    Picture(Picture&& other);

    // Swap this Picture's list with other Picture's list
    void swap(Picture& other);

    // Copy and move assignment for Picture
    Picture& operator=(const Picture& other);
    Picture& operator=(Picture&& other);

    // Adds a clone of shape to the end of this Picture's linked list.
    // Cloning allows us to create any number of shape objects
    // at runtime, while Picture can own the newly created
    // shape objects contained within it. Note this means
    // Picture is responsible for deleting these clones when
    // this Picture object dies.
    void add(const Shape& shape);

    // Calls method print() on each shape in the order they were added
    void print_all(std::ostream& out) const;

    // Draws the Shapes in this Picture in the order they were added
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