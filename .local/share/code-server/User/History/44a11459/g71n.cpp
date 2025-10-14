#include "shape.hpp"
#include <iostream>

Shape::Shape(Point center, std::string name) : center(center), name(name) {}
void Shape::print(std::ostream& out) const {
    out << name << " at (" << center.x << ", " << center.y << ") area = " << area() << std::endl;
}
