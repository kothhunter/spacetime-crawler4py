#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(Point center, std::string name, int width, int height) 
    : Shape(center, std::move(name)), width(width), height(height) {}

double Rectangle::area() const {
    return static_cast<double>(width) * height;
}

void Rectangle::draw(std::ostream& out) const {
    for (int i = 0; i < height; i += 2) {
        for (int j = 0; j < width; ++j) {
            out << '*';
        }
        out << '\n';
    }
}

Rectangle* Rectangle::clone() const {
    return new Rectangle(*this);
}

// void Rectangle::print(std::ostream& out) const {
//     out << name << " at (" << center.x << ", " << center.y << ") area = "
//         << std::fixed << std::setprecision(1) << area() << "\n";
// }
// void Rectangle::print(std::ostream& out) const {
//     out << name << " at (" << center.x << ", " << center.y << ") area = " 
//         << area() << "\n";
// }