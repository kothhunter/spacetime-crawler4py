#include "circle.hpp"
#include <iostream>
#include <numbers>

Circle::Circle(Point center, std::string name, int radius) 
    : Shape(center, std::move(name)), radius(radius) {}

double Circle::area() const {
    return std::numbers::pi * radius * radius;
}

void Circle::draw(std::ostream& out) const {
    for (int y = -radius; y <= radius; y += 2) {
        for (int x = -radius; x <= radius; ++x) {
            out << (x * x + y * y <= radius * radius ? '*' : ' ');
        }
        out << '\n';
    }
}

Circle* Circle::clone() const {
    return new Circle(*this);
}

void Circle::print(std::ostream& out) const {
    out << name << " at (" << center.x << ", " << center.y << ") area = "
        << std::fixed << std::setprecision(1) << area() << "\n";
}