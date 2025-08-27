#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"
#include "mesh.hpp"
#include "objloader.hpp"

int main() {
	GLFWwindow* window = createWindow(800, 600, "OpenGL Multiple Files");
	if (!window) return -1;

	initGLEW();

	// Create VAOs/VBOs
	Object3D myObject = loadOBJ("dummy.obj");

	while (!glfwWindowShouldClose(window)) {
		processInput(window); // optional input function

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw all meshes
		for (auto& mesh : myObject.meshes) {
			if (mesh.textureID != 0)
				glBindTexture(GL_TEXTURE_2D, mesh.textureID);
			glBindVertexArray(mesh.VAO);
			glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

