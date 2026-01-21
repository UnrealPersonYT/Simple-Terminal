# Makefile for Simple-Terminal

# Compiler (default to g++)
CXX ?= g++

# Source files
SRC := .src/main.cpp
TARGET := Simple-Terminal.exe

# Detect compiler and set flags
ifeq ($(findstring g++,$(CXX)),g++)
    CXXFLAGS := -Wall -O3 -s
else ifeq ($(findstring clang++,$(CXX)),clang++)
    CXXFLAGS := -Wall -O3 -s
else ifeq ($(findstring cl,$(CXX)),cl)
    CXXFLAGS := /W3 /O2 /EHsc /GL /MD /Gy
endif

# Compile the executable
$(TARGET): $(SRC)
ifeq ($(findstring cl,$(CXX)),cl)
	$(CXX) $(CXXFLAGS) $(SRC) /Fe$(TARGET)
else
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
endif

ifeq ($(OS),Windows_NT)
    RM := del /Q
else
    RM := rm -f
endif

# Clean build artifacts
clean:
	$(RM) $(TARGET)