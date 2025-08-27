#include "mesh.hpp"
#include <iostream>

// Move constructor
Mesh::Mesh(Mesh&& other)
    : vertices(std::move(other.vertices)),
      VAO(other.VAO),
      VBO(other.VBO),
      vertexCount(other.vertexCount),
      textureID(other.textureID)
{
	other.VAO = 0;
	other.VBO = 0;
}

// Destructor: automatically cleans up OpenGL resources
Mesh::~Mesh()
{
	if (VBO)
		glDeleteBuffers(1, &VBO);
	if (VAO)
		glDeleteVertexArrays(1, &VAO);
}

// Setup VAO/VBO and upload vertex data
void Mesh::setup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

	// layout: position (3 floats) + color (3 floats)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	vertexCount = vertices.size() / 6; // 6 floats per vertex
}

