// buffers.cpp
#include "buffers.hpp"
#include <iostream>

Mesh loadOBJ(const std::string& path)
{
	Mesh mesh;

	mesh.vertices = {
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	}
	setupMesh(mesh);
	return (mesh);
}

void createTriangleBuffers(float* vertices, int vertexCount, GLuint* VAO, GLuint* VBO)
{
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void setupMesh(Mesh& mesh)
{
	glGenVertexArrays(1, &mesh.VAO);
	glGenBuffers(1, &mesh.VBO);

	glBindVertexArray(mesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

	// assume layout: pos (3), color (3)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	mesh.vertexCount = mesh.vertices.size() / 6; // 6 floats per vertex
}


GLuint createShaderProgram() {
	return 0; // placeholder
}
