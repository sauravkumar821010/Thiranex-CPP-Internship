CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = ttt

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
