# Makefile for the Huffman Coding Demo
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = huffman_demo

all: $(TARGET)

$(TARGET): huffman.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) huffman.cpp

clean:
	rm -f $(TARGET) sample.txt compressed_in_memory.bin
