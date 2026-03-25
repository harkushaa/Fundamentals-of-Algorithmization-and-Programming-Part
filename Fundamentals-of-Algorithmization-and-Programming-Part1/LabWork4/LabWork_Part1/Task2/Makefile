CXX = g++
CXXFLAGS = -std=c++17 -I /usr/include -pthread

SRCS = main.cpp
TEST_SRCS = test/main_test.cpp
TEST_TARGET = test_main

all: main

main: $(SRCS)
	$(CXX) $(CXXFLAGS) -o main $(SRCS)

test: $(TEST_SRCS) $(SRCS) 
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRCS) $(SRCS) -lgtest -lgtest_main -pthread
	./$(TEST_TARGET)

clean:
	rm -f main $(TEST_TARGET)
