#include "meshBuffer.hpp"
#include <GL/glew.h> // Needed for glGenBuffers, glBindBuffer, etc.

MeshBuffer::MeshBuffer(const std::vector<float>& vertices,
                       const std::vector<unsigned int>& indices)
{
    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Generate and bind EBO (indices)
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Tell OpenGL how to interpret vertex data
    // For now: assume each vertex is 3 floats (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    // Unbind (VAO keeps the state)
    glBindVertexArray(0);
}

MeshBuffer::~MeshBuffer()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void MeshBuffer::bind() const
{
    glBindVertexArray(VAO);
}

void MeshBuffer::unbind() const
{
    glBindVertexArray(0);
}
