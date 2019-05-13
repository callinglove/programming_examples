import HelloWorld

# In zoo.cpp we expose hello() function, and it now exists in the zoo module.
assert 'hello' in dir(HelloWorld)
# zoo.hello is a callable.
assert callable(HelloWorld.hello)
# Call the C++ hello() function from Python.
print HelloWorld.hello()
