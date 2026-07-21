CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = bank

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) accounts.dat

.PHONY: all run clean
