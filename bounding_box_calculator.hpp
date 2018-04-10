#ifndef __BOUNDING_BOX_CALCULATOR_HPP
#define __BOUNDING_BOX_CALCULATOR_HPP

#include "shape_visitor.hpp"

class BoundingBoxCalculator : public ShapeVisitor
{
public:
    void visitShape(const Circle &);
    void visitShape(const Square &);

    float getBottom() const;
    float getLeft() const;
    float getRight() const;
    float getTop() const;

private:
    float bottom;
    float left;
    float right;
    float top;
};

#endif
