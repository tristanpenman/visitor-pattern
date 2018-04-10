#include "circle.hpp"
#include "shape_visitor.hpp"

Circle::Circle(float x, float y, float radius)
    : Shape(x, y)
    , radius(radius)
{

}

void Circle::accept(ShapeVisitor & visitor) const
{
    visitor.visitShape(*this);
}

float Circle::getRadius() const
{
    return radius;
}
