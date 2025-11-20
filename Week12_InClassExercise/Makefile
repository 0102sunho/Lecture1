# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra


# Source files

SRCS_STARTER = starter.cpp


# Objects
OBJS_STARTER = $(SRCS_STARTER:.cpp=.o)


# target
all: starter

starter: $(OBJS_STARTER)
	$(CXX) $(CXXFLAGS) -o $@ $^


# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up build files
clean:
	rm -f *.o answer test

# Phony targets
.PHONY: all clean