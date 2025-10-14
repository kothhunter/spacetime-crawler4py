// class Shape 
#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iosfwd>
#include <string>

struct Point {
    int x;
    int y;
};

class Shape {
public:
    // Construct this Shape with given center and name
    Shape(Point center, std::string name);

    // Prints this Shape’s name and coordinates
    // in this specific format followed by a newline:
    // name(center.x, center.y), e.g., Circle_2(1, 2)
    void print(std::ostream& out) const;

    // Delete assignment to prevent accidental slicing
    Shape& operator=(const Shape& other) = delete;

    // Computes and returns the area of this Shape
    virtual double area() const = 0;

    // Draws this Shape using character graphics
    // (using algorithms given in write-up)
    virtual void draw(std::ostream& out) const = 0;

    // Create a new duplicate of this Shape
    // allocated from the free store
    // must be over-ridden by each concrete class
    // to return a copy of itself
    virtual Shape* clone() const = 0;

    // Clean up any sub-storage owned by this Shape object
    virtual ~Shape() = default;

protected:
    // Protect the copy constructor to be used only by clone()
    Shape(const Shape& other) = default;

private:
    // Position coordinates, used to illustrate inheritance
    Point center;

    // The name of this shape (supplied to constructor)
    std::string name;
};

#endif