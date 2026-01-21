# Makefile for Simple-Terminal

# Compiler (default to g++)
CXX ?= g++

# Source file
SRC := .src/main.cpp

# Version
VERSION = v1.0.0

# Target executable with version in the name if not defined
TARGET ?= Simple-Terminal-$(VERSION)
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
endif

# Detect compiler and set flags
ifeq ($(findstring g++,$(CXX)),g++)
    CXXFLAGS := -Wall -O3 -s -flto -ffunction-sections -fdata-sections
else ifeq ($(findstring clang++,$(CXX)),clang++)
    CXXFLAGS := -Wall -O3 -s -flto -ffunction-sections -fdata-sections
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