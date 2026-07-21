CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = sms

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) students.dat

.PHONY: all run clean
