#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"
#include "mesh.hpp"
#include "objloader.hpp"
#include "shaders.hpp"

int main() {
	GLFWwindow* window = createWindow(800, 600, "OpenGL Multiple Files");
	if (!window)
		return -1;

	initGLEW();

	// Create VAOs/VBOs
	Object3D myObject = loadOBJ("dummy.obj");
// from here
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO (stores all the buffer bindings + attribute config)
	glBindVertexArray(VAO);

	// Bind and fill VBO with vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		myObject.vertices.size() * sizeof(float),
		myObject.vertices.data(),
		GL_STATIC_DRAW);


	// Bind and fill EBO with index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		myObject.triangles.size() * sizeof(unsigned int),
		myObject.triangles.data(),
		GL_STATIC_DRAW);


	// Configure vertex attribute (layout location = 0)
	// Each vertex = 3 floats, no offset, tightly packed
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
// to here need to make in another file
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
		//
		glBindVertexArray(VAO);
		// maybe need to change this to every form possible
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

//to move with the constructor in a class maybe
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
//end here
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

