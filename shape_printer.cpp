#include <iostream>

#include "circle.hpp"
#include "shape_printer.hpp"
#include "square.hpp"

void ShapePrinter::visitShape(const Circle & circle)
{
    std::cout << "Circle "
        << "{ x: " << circle.getX()
        << ", y: " << circle.getY()
        << ", radius: " << circle.getRadius()
        << " } " << std::endl;
}

void ShapePrinter::visitShape(const Square & square)
{
    std::cout << "Square "
        << "{ x: " << square.getX()
        << ", y: " << square.getY()
        << ", width: " << square.getWidth()
        << ", height: " << square.getHeight()
        << " } " << std::endl;
}
