# I always include these variables for C++ compiling
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
EXECUTABLE 	= typist


PROJECTFILE = Method.cpp Method.hpp Operator.hpp Operator.cpp FittsLaw.hpp FittsLaw.cpp Emma.hpp Emma.cpp benchmark.cpp keyLayout.hpp 

# Scheduler recipe depends on the object files being built
$(EXECUTABLE): $(PROJECTFILE)
	$(CXX) $(CXXFLAGS) $(PROJECTFILE) -o $(EXECUTABLE)


f: 
f: FittsLaw.cpp Constants.hpp
	$(CXX) $(CXXFLAGS) FittsLaw.cpp -o f

b:
b:	benchmark.cpp Constants.hpp
	$(CXX) $(CXXFLAGS) benchmark.cpp -o b

clean:
	rm  -f typist 