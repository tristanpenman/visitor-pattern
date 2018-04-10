# Visitor Pattern

_Notes for a micro-talk given at the [Melbourne C++ Meetup](https://www.meetup.com/MelbourneCpp)._

## Overview

The [Visitor Pattern](https://en.wikipedia.org/wiki/Visitor_pattern) is a way to separate an algorithm from an object structure on which it operates.

What this means is that we can apply a new algorithm to the classes in an object structure, without changing those classes.

## Motivation

### Shapes

As a simple example, consider 2D shapes - in this case circles and squares.

Both shapes have a position in space, represented as X and Y coordinates. We can provide functions to access those members in our Shape base class.

Our application will allow us to calculate the total area for a collection of shapes, so we have a virtual function for calculating the area of a shape:

    class Shape
    {
    public:
        virtual ~Shape() = default;
        float getX() const;
        float getY() const;
        virtual float getArea() const = 0;
    protected:
        Shape(float x, float y);
    private:
        ...
    };

We can declare a class for squares like so:

    class Square : public Shape
    {
    public:
        Square(float x, float y, float width, float height);
        float getArea() const;
        float getHeight() const;
        float getWidth() const;
    private:
        ...
    };

And circles:

    class Circle : public Shape
    {
    public:
        Circle(float x, float y, float radius);
        float getArea() const;
        float getRadius() const;
    private:
        ...
    };

The details of the `getArea()` function are not important - simply note that we have to implement this for every shape.

### Application

Our application logic might look like this:

    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(-1.f, 2.f, 0.5f));
    shapes.push_back(std::make_shared<Square>(12.f, 3.f, 1.2f, 3.4f));

    float totalArea = 0.f;
    for (auto shape : shapes) {
        totalArea += shape->getArea();
    }

### Extension

Now we want to find the bounding box for that collection of shapes. We can imagine a few changes to our Shape base class that would allow for this:

    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(-1.f, 2.f, 0.5f));
    shapes.push_back(std::make_shared<Square>(12.f, 3.f, 1.2f, 3.4f));

    float left = 0.f;
    float right = 0.f;
    float top = 0.f;
    float bottom = 0.f;
    for (auto shape : shapes) {
        left = std::min(left, shape->getLeft());
        right = std::max(right, shape->getRight());
        top = std::min(top, shape->getTop());
        bottom = std::max(bottom, shape->getBottom());
    }

But this is what our Square class looks like now:

    class Square : public Shape
    {
    public:
        Square(float x, float y, float width, float height);
        float getArea() const;
        float getBottom() const;
        float getHeight() const;
        float getLeft() const;
        float getRight() const;
        float getTop() const;
        float getWidth() const;
    private:
        ...
    };

This isn't too bad. Say we now we want to print out a description of our shapes, but only have access to the shapes via a `Shape` pointer or reference... we might implement this like so:

    #include <iostream>

    void Square::print()
    {
        std::cout << "Square "
            << "{ x: " << getX()
            << ", y: " << getY()
            << ", width: " << w
            << ", height: " << h
            << " } " << std::endl;
    }

Damn... the implementation of Square now includes `iostream`. This also hard-codes the string representation for each kind of shape. You can see how this quickly becomes unmaintainble.

## Solution

### Visitor

We can solve this using a _Visitor_ base class:

    class ShapeVisitor
    {
    public:
        virtual ~ShapeVisitor() = default;
        virtual void visitShape(const Circle &) = 0;
        virtual void visitShape(const Square &) = 0;
    };

This gives us a generic way to encapsulate an algorithm, which can then be 'accepted' by a Shape:

    class Shape
    {
    public:
        virtual ~Shape() = default;
        float getX() const;
        float getY() const;
        virtual void accept(ShapeVisitor &) = 0;    // Visitor pattern at work
    protected:
        Shape(float x, float y);
    private:
        ...
    };

Allowing the shape can call the correct version of the `visitShape` function on the visitor (passing itself by reference):

    void Square::accept(ShapeVisitor & visitor)
    {
        visitor.visitShape(*this);
    }

### Bounding Box Calculator

Now we can implement our bounding box algorithm as a visitor, using just the essential information exposed by each kind of `Shape`:

    void BoundingBoxCalculator::visitShape(const Circle & circle)
    {
        const float x = circle.getX();
        const float y = circle.getY();
        const float radius = circle.getRadius();

        bottom = std::max(bottom, y + radius);
        left = std::min(left, x - radius);
        right = std::max(right, x + radius);
        top = std::min(top, y - radius);
    }

    ...

### Shape Printer

And how about a visitor for printing `Shape` descriptions:

    #include <iostream>

    void ShapePrinter::visitShape(const Square & square)
    {
        std::cout << "Square "
            << "{ x: " << square.getX()
            << ", y: " << square.getY()
            << ", width: " << square.getWidth()
            << ", height: " << square.getHeight()
            << " } " << std::endl;
    }

    ...

### Updated Application Logic

This is our updated application logic, with the bounding box algorithm neatly tucked away inside a visitor.

    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(-1.f, 2.f, 0.5f));
    shapes.push_back(std::make_shared<Square>(12.f, 3.f, 1.2f, 3.4f));

    BoundingBoxCalculator calculator;
    for (auto shape : shapes) {
        shape->accept(calculator);
    }

## Further Discussion

### Object Heirarchies

Visitors are not limited to being applied to flat collections. They can also be passed along in object heirarchies, or graphs. This is the approach that I used in my JSON Schema validation library ([valijson](https://github.com/tristanpenman/valijson)) to perform validation.

I have also used this approach in a Ray-Tracing renderer. While the overhead of virtual dispatch meant that a visitor was not viable for actual rendering, visitors are used for pre-processing and optimising a scene graph prior to rendering.

### Function Overloading

In the example above, the `ShapeVisitor` base class used function overloading for the `visitShape` function. This is not required by the pattern. You could instead have different function names for each kind of shape, e.g:

    visitCircle(const Circle &);
    visitSquare(const Square &);

### Const vs Non-Const

You might have noticed that the various overloads for the `ShapeVisitor::visitShape` function used `const` references

When considering use of the Visitor Pattern, I have not found it necessary (or appropriate) to modify objects via a visitor. Of course, your experience may differ, so my recommendation is to err on the side of using `const` references until you decide to implement a visitor that will actually modify an object heirarchy.

## Code

This directory contains example code that can be used as a reference.

It has been compiled and tested using `clang++`:

    clang++ std=c++11 *.cpp
    ./a.out

## Other Patterns

Interested in learning more about design patterns?

Commonly known as the 'Gang of Four' (or GoF) book, _[Design Patterns: Elements of Reusable Object-Oriented Software](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612)_ is a classic design patterns reference, which describes 23 patterns in detail.

And courtesy of fellow Melbourne C++ programmer, [José Miguel Armijo Fidalgo](https://github.com/jm-armijo) you'll find a reference implementation of the [Abstract Factory pattern](https://en.wikipedia.org/wiki/Abstract_factory_pattern), amongst others.

## License

These templates are in the public domain. You may use or modify it in any way you like, and no attribution is required.
