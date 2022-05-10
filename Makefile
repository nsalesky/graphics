CC = gcc
CXX = g++
CFLAGS = -Wall -g -std=c++17 -lmingw32 -lSDL2main -lSDL2

INCLUDES = -Iinclude
OBJS = src/main.cpp src/application.cpp src/glad.c

default: all

all: $(OBJS)
	$(CXX) $(OBJS) $(CFLAGS) $(INCLUDES) -o graphics

clean:
	$(RM) graphics.exe *.o