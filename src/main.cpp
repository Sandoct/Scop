#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"
#include "mesh.hpp"
#include "objloader.hpp"
#include "shaders.hpp"
#include "meshBuffer.hpp"

int main() {
	GLFWwindow* window = createWindow(800, 600, "OpenGL Multiple Files");
	if (!window)
		return -1;

	initGLEW();

	Object3D myObject = loadOBJ("dummy.obj");
	MeshBuffer	buff = MeshBuffer(myObject.vertices, myObject.triangles);

// tmp sahder setup need to create own file
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";
// Fragment Shader source
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // orange color
}
)";

Shader shader(vertexShaderSource, fragmentShaderSource);
//

	while (!glfwWindowShouldClose(window)) {
		processInput(window); // optional input function

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//temp shader usage
		shader.use();
		buff.bind();
		// maybe need to change this to every form possible
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	buff.unbind();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

