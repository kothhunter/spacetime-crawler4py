#include <iostream>
#include <string>
#include "picture.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"
using namespace std;

int main(int argc, char * argv[])
{
    cout << argv[argc-1] << " says Hello World\n";
}

constexpr int N_TESTS = 15;
constexpr int PIDEFAULT = 2;
constexpr int P2DEFAULT = 3;

void add_shapes(Picture& p, int i, int param1, int param2) {
    p.add(Circle{ {0, 0}, "Circle" + to_string(i), i * param1 });
    p.add(Square{ {0, 0}, "Square" + to_string(i), i * param1 });
    p.add(Triangle{ {0, 0}, "Triangle" + to_string(i), i * param1, i * param2 });
    p.add(Rectangle{ {0, 0}, "Rectangle" + to_string(i), i * param1, i * param2 });
}

int get_param(int num, int argc, char** argv, int def) {
    return argc > num ? atoi(argv[num]) : def;
}

int main(int argc, char** argv) {
    int param1 = get_param(1, argc, argv, PIDEFAULT);
    int param2 = get_param(2, argc, argv, P2DEFAULT);
    Picture collage;
    for (int i = 1; i <= N_TESTS; ++i)
        add_shapes(collage, i, param1, param2);
    cout << "Total Area = " << collage.total_area() << endl;
    collage.print_all(cout);
    collage.draw_all(cout);
}

//main given in this cpp, not instructions
// int main(int argc, char * argv[])
// {
//     cout << argv[argc-1] << " says Hello World\n";
// }