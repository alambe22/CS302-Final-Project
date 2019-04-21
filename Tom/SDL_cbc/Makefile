CXX=	  g++
CXXFLAGS= -w -lSDL2 -std=c++11
LDFLAGS=
SHELL=	  bash
PROGRAMS= cbc
SOURCES= cbc.cpp Map.cpp Units.cpp PerlinNoise.cpp
OBJECTS= $(SOURCES:.cpp=.o)

all:	 $(PROGRAMS)

%.o: 	 %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

cbc: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

clean:
	rm -f $(PROGRAMS) $(OBJECTS)
