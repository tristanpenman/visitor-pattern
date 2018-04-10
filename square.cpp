#include "shape_visitor.hpp"
#include "square.hpp"

void Square::accept(ShapeVisitor & visitor) const
{
    visitor.visitShape(*this);
}

float Square::getHeight() const
{
    return height;
}

float Square::getWidth() const
{
    return width;
}
