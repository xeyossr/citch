CXX = g++
CXXFLAGS = -Wall -std=c++17

TARGET = citch
SRC = citch.cpp modules/banners.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

