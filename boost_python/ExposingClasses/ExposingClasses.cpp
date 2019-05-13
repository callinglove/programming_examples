#include <Python.h>
#include <boost/python.hpp>


struct World
{
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};


BOOST_PYTHON_MODULE(ExposingClasses)
{
    using namespace boost::python;
    
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
}
