#include "meshBuffer.hpp"

MeshBuffer::MeshBuffer(const std::vector<float>& vertices,
                       const std::vector<unsigned int>& indices,
                       const std::vector<float>& colors,
                       const std::vector<float>& texCoords)
{
    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO_color);
	glGenBuffers(1, &VBO_text);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // Colors
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	//texture
	glBindBuffer(GL_ARRAY_BUFFER, VBO_text);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

MeshBuffer::~MeshBuffer()
{
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO_text);
    glDeleteBuffers(1, &VBO_color);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void MeshBuffer::bind() const { glBindVertexArray(VAO); }
void MeshBuffer::unbind() const { glBindVertexArray(0); }

void MeshBuffer::updateColors(const std::vector<float>& colors)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferSubData(GL_ARRAY_BUFFER, 0, colors.size() * sizeof(float), colors.data());
}

