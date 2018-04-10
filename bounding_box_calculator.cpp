#include <algorithm>

#include "bounding_box_calculator.hpp"
#include "circle.hpp"
#include "square.hpp"

float BoundingBoxCalculator::getBottom() const
{
    return bottom;
}

float BoundingBoxCalculator::getLeft() const
{
    return left;
}

float BoundingBoxCalculator::getRight() const
{
    return right;
}

float BoundingBoxCalculator::getTop() const
{
    return top;
}

void BoundingBoxCalculator::visitShape(const Circle & circle)
{
    const float x = circle.getX();
    const float y = circle.getY();
    const float radius = circle.getRadius();

    bottom = std::max(bottom, y + radius);
    left = std::min(left, x - radius);
    right = std::max(right, x + radius);
    top = std::min(top, y - radius);
}

void BoundingBoxCalculator::visitShape(const Square & square)
{
    const float x = square.getX();
    const float y = square.getY();
    const float halfWidth = square.getWidth() / 2.f;
    const float halfHeight = square.getHeight() / 2.f;

    bottom = std::max(bottom, y + halfWidth);
    left = std::min(left, x - halfHeight);
    right = std::max(right, x + halfWidth);
    top = std::min(top, y - halfHeight);
}
