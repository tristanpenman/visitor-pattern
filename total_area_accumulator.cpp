#include <cmath>

#include "circle.hpp"
#include "square.hpp"
#include "total_area_accumulator.hpp"

float TotalAreaAccumulator::getTotalArea() const
{
    return totalArea;
}

void TotalAreaAccumulator::visitShape(const Circle & circle)
{
    const float radius = circle.getRadius();

    totalArea += radius * radius * M_PI;
}

void TotalAreaAccumulator::visitShape(const Square & square)
{
    totalArea += square.getWidth() * square.getHeight();
}
