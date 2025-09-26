#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"
#include "objloader.hpp"
#include "texloader.hpp"
#include "shaders.hpp"
#include "meshBuffer.hpp"
#include "matrix4.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
		return -1;
	GLFWwindow* window = createWindow(800, 600, "OpenGL Multiple Files");
	if (!window)
		return -1;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// creating the obj and trying load it with the .obj
	Object3D myObject;
	try {
		myObject = loadOBJ(argv[1]);
	} catch (const std::exception& e) {
		std::cerr << "Error loading OBJ: " << e.what() << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	// creating mesh from the vertex and face of the object
	MeshBuffer	buff = MeshBuffer(myObject.vertices, myObject.triangles, myObject.defaultColors, myObject.texCoords);

	// loading shaders
	Shader shader(getVertexShaderSource(), getFragmentShaderSource());

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

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

		static bool useTexture = false;
		static bool lastTState = false;

		// Check key press for texture
		bool tPressed = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
		if (tPressed && !lastTState)
		{
			useTexture = !useTexture;
			if (useTexture)
			{
				Material& mat = myObject.materials[myObject.currentMaterial];
				if (mat.textureID != 0)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, mat.textureID);
					shader.use();
					shader.setInt("texture1", 0);
				} else
				{
					buff.updateColors(myObject.materialColors);
				}
			} 
			else
			{
				buff.updateColors(myObject.defaultColors);
			}
		}
		lastTState = tPressed;

		//matrix
		static float	angle_h = 0.0f;  // keeps value across frames
		static float	angle_v = 0.0f;  // keeps value across frames
		static bool		lastRState = false;
		static bool		rState = false;
		// Check key press for rotation
		bool rPressed = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;
		if (rPressed && !lastRState)
			rState = !rState;
		lastRState = rPressed;
		if (rState)
			angle_h += 0.01f;             // small rotation per frame
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) angle_h += 0.03f; // forward
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) angle_h -= 0.03f; // forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) angle_v += 0.03f; // forward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) angle_v -= 0.03f; // forward

		Matrix4 rotation = Matrix4::multiply(Matrix4::rotateY(angle_h), Matrix4::rotateX(angle_v));
		Matrix4 model = Matrix4::multiply(Matrix4::translate(pos.X, pos.Y, pos.Z), rotation);
		Matrix4 view  = Matrix4::translate(0, 0, -3);
		Matrix4 proj  = Matrix4::perspective(45.0f * M_PI / 180.0f, ((float)800/(float)600), 0.1f, 100.0f);


		// Pass MVP to shader
		shader.use();
		shader.setMat4("model", model.m);
		shader.setMat4("view", view.m);
		shader.setMat4("projection", proj.m);
		shader.setBool("useTexture", useTexture);

		buff.bind();
		glDrawElements(GL_TRIANGLES, myObject.triangles.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	buff.unbind();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

