CXX=	  g++
CXXFLAGS= -g -Wall -std=gnu++11
LDFLAGS=
SHELL=	  bash
PROGRAMS= challenge8
SOURCES= solution.cpp map.cpp unit.cpp graphics.cpp
OBJECTS= $(SOURCES:.cpp=.o)

all:	 $(PROGRAMS)

%.o: 	 %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

solution: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -f $(PROGRAMS) $(OBJECTS)


