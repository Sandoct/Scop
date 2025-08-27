// buffers.hpp
#pragma once
#include <GL/glew.h>

struct Mesh
{
	std::vector<float> vertices;  // interleaved: pos, color, tex, normal
	GLuint VAO;
	GLuint VBO;
	size_t vertexCount;
};

Mesh loadOBJ(const std::string& path);
void createTriangleBuffers(float* vertices, int vertexCount, GLuint* VAO, GLuint* VBO);
GLuint createShaderProgram(); // optional shader creation here
