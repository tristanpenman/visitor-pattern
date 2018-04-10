#ifndef __SHAPE_HPP
#define __SHAPE_HPP

class ShapeVisitor;

class Shape
{
public:
    virtual ~Shape() = default;

    virtual void accept(ShapeVisitor &) const = 0;

    float getX() const;
    float getY() const;

protected:
    Shape(float x, float y);

private:
    const float x;
    const float y;
};

#endif
