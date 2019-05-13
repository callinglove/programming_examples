//http://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/tutorial/tutorial/exposing.html#tutorial.exposing.constructors


#include <Python.h>
#include <boost/python.hpp>


struct Var
{
    Var(std::string name): name(name), value() {}
    std::string const name;
    float value;
};


BOOST_PYTHON_MODULE(ClassDataMembers)
{
    using namespace boost::python;
    
    class_<Var>("Var", init<std::string>())
        .def_readonly("name", &Var::name)
        .def_readwrite("value", &Var::value)
    ;
}
