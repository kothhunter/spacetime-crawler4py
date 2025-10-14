#include "circle.hpp"
#include <iostream>
#include <numbers>

// constructor - Initializes Circle with center point, name, and radius
Circle::Circle(Point center, std::string name, int radius) 
    : Shape(center, std::move(name)), radius(radius) {}

// Computes and returns the area of the Circle
double Circle::area() const {
    return std::numbers::pi * radius * radius;
}

// Draws the Circle using simple character graphics (placeholder implementation)
void Circle::draw(std::ostream& out) const {
    for (int y = -radius; y <= radius; y += 2) {
        for (int x = -radius; x <= radius; ++x) {
            out << (x * x + y * y <= radius * radius ? '*' : ' ');
        }
        out << '\n';
    }
}

// Creates a new duplicate of this Circle object allocated from the free store
Circle* Circle::clone() const {
    return new Circle(*this);
}