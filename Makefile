CC = gcc
CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -lmingw32 -lSDL2main -lSDL2

INCLUDES = -Iinclude

#TODO: I shouldn't have to manually add each source file here, figure out how to automate it for src/*.cpp
OBJS = src/main.cpp src/Application.cpp src/SceneNode.cpp src/Transform.cpp src/Shader.cpp src/GeometryBuilder.cpp src/Geometry.cpp src/Util.cpp src/ShaderManager.cpp src/Camera.cpp src/CameraManager.cpp src/FreeFlyCamera.cpp src/CubeNode.cpp src/glad.c

default: all

all: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(INCLUDES) -o graphics

clean:
	$(RM) graphics.exe *.o