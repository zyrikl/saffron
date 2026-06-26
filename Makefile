CXX = g++
CXXFLAGS = -std=c++20 -I./src/includes

SRCS := $(shell find . -type f -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)
TARGET = saffron

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install:
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod +x /usr/local/bin/$(TARGET)

build:
	make
	make install

clean:
	rm -f $(OBJS) $(TARGET) .saffron_attributes