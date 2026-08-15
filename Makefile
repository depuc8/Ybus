# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include

# Files
SRC = $(SRC_DIR)/Ybus.cpp
TARGET = Ybus

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Remove generated files
clean:
	rm -f $(TARGET)

# Rebuild from scratch
rebuild: clean all

.PHONY: all clean rebuild
