// window.hpp
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* createWindow(int width, int height, const char* title);
void initGLEW();
void processInput(GLFWwindow* window);
