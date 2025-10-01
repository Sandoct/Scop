#pragma once
#include <glad/glad.h>
#include <vector>

class MeshBuffer
{
	private:
		unsigned int VAO;
		unsigned int EBO;
		unsigned int VBO;
		unsigned int VBO_color;
		unsigned int VBO_text;

	public:
		MeshBuffer(const std::vector<float>& vertices,
				const std::vector<unsigned int>& indices,
				const std::vector<float>& colors,
				const std::vector<float>& texCoords);

		~MeshBuffer();

		void bind() const;
		void unbind() const;

		void updateColors(const std::vector<float>& colors);

};
