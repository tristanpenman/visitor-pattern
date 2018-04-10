#include "shape.hpp"

Shape::Shape(float x, float y)
    : x(x)
    , y(y)
{

}

float Shape::getX() const
{
    return x;
}

float Shape::getY() const
{
    return y;
}