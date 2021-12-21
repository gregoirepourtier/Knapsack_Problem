CXX = g++
CXXFLAGS = -Wall -g -std=c++11
SRCS = bruteforce.cpp dp1.cpp dp2.cpp files.cpp heuristic.cpp main.cpp

OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=%.d)

myExe : $(OBJS)
				$(CXX) $^ -o $@

-include $(DEPS)

%.o : %.cpp
				$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean :
				rm -rf *.o *.d *~ *myExe
