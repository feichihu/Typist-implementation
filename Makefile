# I always include these variables for C++ compiling
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
EXECUTABLE 	= typist


PROJECTFILE = Method.cpp Method.hpp Operator.hpp Operator.cpp FittsLaw.hpp FittsLaw.cpp Emma.hpp Emma.cpp main.cpp

# Scheduler recipe depends on the object files being built
$(EXECUTABLE): $(PROJECTFILE)
	$(CXX) $(CXXFLAGS) $(PROJECTFILE) -o $(EXECUTABLE)


f: 
f: FittsLaw.cpp Constants.hpp
	$(CXX) $(CXXFLAGS) FittsLaw.cpp -o f

clean:
	rm  -f typist 