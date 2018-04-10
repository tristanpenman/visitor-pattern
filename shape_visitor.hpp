#ifndef __SHAPE_VISITOR_HPP
#define __SHAPE_VISITOR_HPP

class Circle;
class Square;

class ShapeVisitor
{
public:
    virtual ~ShapeVisitor() = default;

    virtual void visitShape(const Circle &) = 0;
    virtual void visitShape(const Square &) = 0;
};

#endif
