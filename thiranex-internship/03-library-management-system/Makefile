CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = library

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) books.dat members.dat

.PHONY: all run clean
