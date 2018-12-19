# Makefile for compiling the program test_heap
# variable definition

CC = g++
MAINSRCS = main.cpp
OTHSRCS = 
HEADERS = 
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = main #$(MAINSRCS:.cpp=)
MEMCHECKARGS = 

CFLAGS = -g -Wall -O2 -std=c++11

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) < 20.in $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all memcheck clean
