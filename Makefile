CC = gcc
CXX = g++
CFLAGS = -Wall -g -std=c++17 -lmingw32 -lSDL2main -lSDL2

INCLUDES = -Iinclude
OBJS = src/main.cpp src/Application.cpp src/SceneNode.cpp src/Transform.cpp src/Shader.cpp src/GeometryBuilder.cpp src/Geometry.cpp src/Util.cpp src/CubeNode.cpp src/glad.c

default: all

all: $(OBJS)
	$(CXX) $(OBJS) $(CFLAGS) $(INCLUDES) -o graphics

clean:
	$(RM) graphics.exe *.o