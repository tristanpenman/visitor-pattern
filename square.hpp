#ifndef __SQUARE_HPP
#define __SQUARE_HPP

#include "shape.hpp"

class Square : public Shape
{
public:
    Square(float x, float y, float width, float height) : Shape(x, y), width(width), height(height) {}

    virtual void accept(ShapeVisitor &) const;

    float getHeight() const;
    float getWidth() const;

private:
    const float width;
    const float height;
};

#endif
