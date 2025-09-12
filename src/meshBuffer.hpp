#pragma once
#include <vector>

class MeshBuffer
{
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

public:
    // Constructor: takes vertices and indices (triangles)
    MeshBuffer(const std::vector<float>& vertices,
               const std::vector<unsigned int>& indices);

    // Destructor: cleans up GPU resources
    ~MeshBuffer();

    // Binds this buffer (for drawing)
    void bind() const;

    // Unbinds everything
    void unbind() const;

    // For now, disable copying (we can add move semantics later)
    MeshBuffer(const MeshBuffer&) = delete;
    MeshBuffer& operator=(const MeshBuffer&) = delete;
};
