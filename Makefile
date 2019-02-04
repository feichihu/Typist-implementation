# I always include these variables for C++ compiling
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
EXECUTABLE 	= typist
OBJS = typist.o 


PROJECTFILE = Method.cpp Method.hpp Operator.hpp Operator.cpp main.cpp

# Scheduler recipe depends on the object files being built
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXECUTABLE)

typist.o: $(PROJECTFILE)
	$(CXX) $(CXXFLAGS) -c $(PROJECTFILE) -o typist.o


clean:
	rm  -f typist.o 