#ifndef __SHAPE_PRINTER_HPP
#define __SHAPE_PRINTER_HPP

#include "shape_visitor.hpp"

class ShapePrinter : public ShapeVisitor
{
public:
    void visitShape(const Circle &);
    void visitShape(const Square &);
};

#endif
