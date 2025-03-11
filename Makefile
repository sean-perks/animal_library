# Compiler
CXX = g++

# Compiler flags (All warnings, but NOT treated as errors)
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17

# Source files
SRCS = main.cpp fauna.cpp creature.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = program

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean generated files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
