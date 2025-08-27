#pragma once
#include <vector>
#include <GL/glew.h>

class Mesh {
	public :
		std::vector<float>	vertices;
		GLuint	VAO = 0;
		GLuint	VBO = 0;
		size_t	vertexCount = 0;
		GLuint	textureID = 0;

		Mesh() = default;
		Mesh(Mesh&& other);
		~Mesh();

		void setup();
};
