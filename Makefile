# I always include these variables for C++ compiling
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
EXECUTABLE 	= typist


PROJECTFILE = Method.cpp Method.hpp Operator.hpp Operator.cpp main.cpp

# Scheduler recipe depends on the object files being built
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(PROJECTFILE) -o $(EXECUTABLE)

clean:
	rm  -f typist 