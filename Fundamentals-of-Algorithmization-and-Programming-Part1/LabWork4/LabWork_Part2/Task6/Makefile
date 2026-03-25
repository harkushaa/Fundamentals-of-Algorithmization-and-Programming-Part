CXX = g++
CC = gcc
CXXFLAGS = -std=c++17 -I /usr/include -pthread
CFLAGS = -std=c11

SRCS = main.c
OBJS = main.o
TEST_SRCS = test/main_test.cpp
TEST_TARGET = test_main

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

test: $(TEST_SRCS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRCS) $(OBJS) -lgtest -lgtest_main -pthread
	./$(TEST_TARGET)

clean:
	rm -f main $(TEST_TARGET) $(OBJS)
