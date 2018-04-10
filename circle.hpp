#ifndef __CIRCLE_HPP
#define __CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
    Circle(float x, float y, float radius);

    void accept(ShapeVisitor &) const;

    float getRadius() const;

private:
    const float radius;
};

#endif