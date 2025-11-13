# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra


# Source files
SRCS_MAIN = main.cpp
SRCS_VECTOR3D = Vector3D.cpp


# Objects
OBJS_MAIN = $(SRCS_MAIN:.cpp=.o)
OBJS_VECTOR3D = $(SRCS_VECTOR3D:.cpp=.o)


# target
all: main vector3d

main: $(OBJS_MAIN) $(OBJS_VECTOR3D)
	$(CXX) $(CXXFLAGS) -o $@ $^

vector3d: $(OBJS_VECTOR3D)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up build files
clean:
	rm -f *.o answer test

# Phony targets
.PHONY: all clean