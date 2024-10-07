CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = search_engine
SRC = src/main.cpp src/search_engine.cpp src/indexer.cpp src/utils.cpp
OBJ = $(SRC:.cpp=.o)
INCLUDE = -I./include

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
