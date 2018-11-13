CC = g++
MAINSRCS = main.cpp
OTHSRCS =
HEADERS = 
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = main
MEMCHECKARGS = 

CFLAGS = -g -Wall -std=c++11 -O2

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all memcheck clean
