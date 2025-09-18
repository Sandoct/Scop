#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"
#include "objloader.hpp"
#include "shaders.hpp"
#include "meshBuffer.hpp"
#include "matrix4.hpp"

int main(int argc, char** argv)
{
	if (argc < 2)
		return -1;
	GLFWwindow* window = createWindow(800, 600, "OpenGL Multiple Files");
	if (!window)
		return -1;

	initGLEW();

	Object3D myObject;

	try {
		myObject = loadOBJ(argv[1]);
	} catch (const std::exception& e) {
		std::cerr << "Error loading OBJ: " << e.what() << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	MeshBuffer	buff = MeshBuffer(myObject.vertices, myObject.triangles, myObject.defaultColors);
// tmp sahder setup need to create own file
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(aPos, 1.0);
	vertexColor = aColor;
}
)";
// Fragment Shader source
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

void main()
{
	FragColor = vec4(vertexColor, 1.0);
}
)";

	Shader shader(vertexShaderSource, fragmentShaderSource);
//

	while (!glfwWindowShouldClose(window)) {
		processInput(window); // optional input function

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		//rotation
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos.Z -= pos.speed; // forward
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos.Z += pos.speed; // backward
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos.X -= pos.speed; // left
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos.X += pos.speed; // right
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) pos.Y += pos.speed; // up
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) pos.Y -= pos.speed; // down

		static bool useMtlColors = false;
		static bool lastTState = false;
		// Check key
		bool tPressed = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
		if (tPressed && !lastTState)
		{
			useMtlColors = !useMtlColors;
			if (useMtlColors)
				buff.updateColors(myObject.materialColors);
			else
				buff.updateColors(myObject.defaultColors);
		}
		lastTState = tPressed;

		//matrix
		static float angle = 0.0f;  // keeps value across frames
		angle += 0.01f;             // small rotation per frame

		//Matrix4 model = Matrix4::rotateY(angle);
		Matrix4 model = Matrix4::multiply(Matrix4::translate(pos.X, pos.Y, pos.Z), Matrix4::rotateY(angle));
		Matrix4 view  = Matrix4::translate(0, 0, -3);
		Matrix4 proj  = Matrix4::perspective(45.0f * M_PI / 180.0f, ((float)800/(float)600), 0.1f, 100.0f);
		Matrix4 mvp   = Matrix4::multiply(proj, Matrix4::multiply(view, model));

		//temp shader usage
		shader.use();
		buff.bind();
		//matrix p2
		int mvpLoc = glGetUniformLocation(shader.ID, "MVP");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp.m);
		glDrawElements(GL_TRIANGLES, myObject.triangles.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	buff.unbind();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

