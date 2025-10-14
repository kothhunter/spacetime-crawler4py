#include "square.hpp"

Square::Square(Point center, std::string name, int side)
    : Rectangle(center, std::move(name), side, side) {}

Square* Square::clone() const {
    return new Square(*this);
}

void Square::print(std::ostream& out) const {
    out << name << " at (" << center.x << ", " << center.y << ") area = "
        << std::fixed << std::setprecision(1) << area() << "\n";
}