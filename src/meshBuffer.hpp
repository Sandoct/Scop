#pragma once
#include <vector>
#include <GL/glew.h>

class MeshBuffer
{
	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
		unsigned int CBO;

	public:
		MeshBuffer(const std::vector<float>& vertices,
				const std::vector<unsigned int>& indices,
				const std::vector<float>& colors);

		~MeshBuffer();

		void bind() const;
		void unbind() const;

		void updateColors(const std::vector<float>& colors);

		// For now, disable copying (we can add move semantics later)
		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;
};
