//http://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/tutorial/tutorial/exposing.html#tutorial.exposing.constructors


#include <Python.h>
#include <boost/python.hpp>


struct World
{
    World(std::string msg): msg(msg) {}
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};


BOOST_PYTHON_MODULE(SingleConstructor)
{
    using namespace boost::python;
    
    class_<World>("World", init<std::string>())
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
}
