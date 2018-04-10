#ifndef __TOTAL_AREA_ACCUMULATOR_HPP
#define __TOTAL_AREA_ACCUMULATOR_HPP

#include "shape_visitor.hpp"

class TotalAreaAccumulator : public ShapeVisitor
{
public:
    void visitShape(const Circle &);
    void visitShape(const Square &);

    float getTotalArea() const;

private:
    float totalArea;
};

#endif
