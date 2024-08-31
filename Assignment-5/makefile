# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++20
TARGET = main

# Source files (exclude main.cpp from the sibling folder)
SRCS = $(wildcard *.cpp) $(filter-out ../Assignment-4/main.cpp, $(wildcard ../Assignment-4/*.cpp))

# Object files (stored in the build directory with adjusted paths)
OBJS = $(patsubst %.cpp, build/%.o, $(notdir $(SRCS)))

# Default rule: build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule for creating object files in the build directory
build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Special rule for source files in the sibling directory
build/%.o: ../Assignment-4/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build directory
clean:
	rm -rf build $(TARGET)

# Phony targets (they're not actual files)
.PHONY: clean
