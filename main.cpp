#include <iostream>
#include <vector>

#include "bounding_box_calculator.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "shape_printer.hpp"
#include "total_area_accumulator.hpp"

int main(int argc, char **argv)
{
    std::vector<std::shared_ptr<Shape>> shapes;

    shapes.push_back(std::make_shared<Circle>(-1.f, 2.f, 0.5f));
    shapes.push_back(std::make_shared<Square>(12.f, 3.f, 1.2f, 3.4f));

    ShapePrinter printer;
    BoundingBoxCalculator calculator;
    TotalAreaAccumulator accumulator;
    for (auto shape : shapes) {
        shape->accept(printer);
        shape->accept(calculator);
        shape->accept(accumulator);
        std::cout << "  - total area: " << accumulator.getTotalArea() << std::endl;
        std::cout << "  - bounding box: "
                << "{ left: " << calculator.getLeft()
                << ", right: " << calculator.getRight()
                << ", top: " << calculator.getTop()
                << ", bottom: " << calculator.getBottom()
                << " }" << std::endl;
    }

    return 0;
}