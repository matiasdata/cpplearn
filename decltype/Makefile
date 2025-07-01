# Makefile for building main.cpp with Boost

CXX = g++
CXXFLAGS = -Wall -std=c++20 -I/opt/homebrew/opt/boost/include

TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
