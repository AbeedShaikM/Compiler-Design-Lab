# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++23
TARGET = main

# Source files (finds all .cpp files in the directory)
SRCS = $(wildcard *.cpp)

# Object files (stored in the build directory)
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))

# Default rule: build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule for creating object files in the build directory
build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build directory
clean:
	rm -rf build $(TARGET)

# Phony targets (they're not actual files)
.PHONY: clean
