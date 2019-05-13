PYTHON		= python2.7
PYCONFIG	= python2.7-config
PYLIBPATH	= $(shell ${PYCONFIG} --exec-prefix)/lib

CC		= g++
RM		= rm -rf
CFLAGS	= $(shell ${PYCONFIG} --include) -fPIC -O2
LFLAGS	= -L$(PYLIBPATH) $(shell ${PYCONFIG} --libs) -lboost_python
SFLAGS	= -shared -Wl,-soname,$(TARGET).so -Wl,-rpath,$(PYLIBPATH)

TARGET  = HelloWorld
OBJDIR  = .objs
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: build $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(SFLAGS) -o $(TARGET).so $(OBJECTS) $(LFLAGS)

$(OBJECTS): $(OBJDIR)/%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test:
	@${PYTHON} ./test.py

build:
	@mkdir -p $(OBJDIR)

clean:
	@$(RM) $(OBJDIR) $(TARGET).so *.o *~

.PHONY: default clean
