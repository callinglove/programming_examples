//http://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/tutorial/tutorial/exposing.html#tutorial.exposing.inheritance


#include <Python.h>
#include <boost/python.hpp>


struct Shape
{
    virtual ~Shape() {}
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }

    int width;
    int height;
};

struct Rectangle : Shape
{
    int getArea() { return (width*height); }
};

void resetSize(Shape* s) { s->width = 0; s->height = 0; }
Shape* factory() { return new Rectangle; }


BOOST_PYTHON_MODULE(Inheritance)
{
    using namespace boost::python;
    
    class_<Shape>("Shape")
        .def("setWidth", &Shape::setWidth)
        .def("setHeight", &Shape::setHeight)
        .def_readonly("width", &Shape::width)
        .def_readonly("height", &Shape::height)
    ;

    class_<Rectangle, bases<Shape> >("Rectangle")
        .def("getArea", &Rectangle::getArea)
    ;

    def("resetSize", resetSize);
    def("factory", factory, return_value_policy<manage_new_object>());
}
