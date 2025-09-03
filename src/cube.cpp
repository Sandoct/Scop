// Each vertex is a position in 3D space: x, y, z
float vertices[] = {
    // Vertex 0
    -0.5f, -0.5f, -0.5f,  // bottom back left
    // Vertex 1
     0.5f, -0.5f, -0.5f,  // bottom back right
    // Vertex 2
     0.5f,  0.5f, -0.5f,  // top back right
    // Vertex 3
    -0.5f,  0.5f, -0.5f,  // top back left
    // Vertex 4
    -0.5f, -0.5f,  0.5f,  // bottom front left
    // Vertex 5
     0.5f, -0.5f,  0.5f,  // bottom front right
    // Vertex 6
     0.5f,  0.5f,  0.5f,  // top front right
    // Vertex 7
    -0.5f,  0.5f,  0.5f   // top front left
};

unsigned int triangles[][3] = {
    // Back face
    {0, 1, 2},
    {2, 3, 0},

    // Front face
    {4, 5, 6},
    {6, 7, 4},

    // Left face
    {0, 3, 7},
    {7, 4, 0},

    // Right face
    {1, 5, 6},
    {6, 2, 1},

    // Bottom face
    {0, 1, 5},
    {5, 4, 0},

    // Top face
    {3, 2, 6},
    {6, 7, 3}
};

