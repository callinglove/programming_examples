//http://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/tutorial/tutorial/exposing.html#tutorial.exposing.constructors


#include <Python.h>
#include <boost/python.hpp>


struct Num
{
    public:
        Num() {}
        float get() const {return v;}
        void set(float value) {v = value;}

    private:
        float v;
};


BOOST_PYTHON_MODULE(ClassProperties)
{
    using namespace boost::python;
    
    class_<Num>("Num", init<>())
        .add_property("rovalue", &Num::get)
        .add_property("value", &Num::get, &Num::set)
    ;
}
