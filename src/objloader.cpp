#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <cfloat>
#include <iostream>
#include "mesh.hpp"
#include "objloader.hpp"

/* Temporary OBJ loader — just returns multiple simple triangles
Object3D loadOBJ(const std::string& path)
{
	(void) path;
    Object3D cube;

    // 8 corner vertices
    cube.vertices = {
        -0.5f, -0.5f, -0.5f, // 0
         0.5f, -0.5f, -0.5f, // 1
         0.5f,  0.5f, -0.5f, // 2
        -0.5f,  0.5f, -0.5f, // 3
        -0.5f, -0.5f,  0.5f, // 4
         0.5f, -0.5f,  0.5f, // 5
         0.5f,  0.5f,  0.5f, // 6
        -0.5f,  0.5f,  0.5f  // 7
    };

    // 12 triangles
    cube.triangles = {
        0, 1, 2, 2, 3, 0, // back
        4, 5, 6, 6, 7, 4, // front
        0, 3, 7, 7, 4, 0, // left
        1, 5, 6, 6, 2, 1, // right
        0, 1, 5, 5, 4, 0, // bottom
        3, 2, 6, 6, 7, 3  // top
    };

    return cube;
}

*/
Object3D loadOBJ(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
		throw std::runtime_error("Could not open file");

	Object3D obj;
	std::vector<std::array<float, 3>> temp_vertices;
	std::string line;

	while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
		{
            float x, y, z;
            if (!(ss >> x >> y >> z))
                throw std::runtime_error("Invalid vertex line: " + line);
            temp_vertices.push_back({x, y, z});
        }
        else if (prefix == "f")
		{
			std::vector<unsigned int> faceVertices;
			unsigned int idx;

			// read all vertex indices in this face
			while (ss >> idx)
			{
				if (idx == 0 || idx > temp_vertices.size())
					throw std::runtime_error("Face references non-existent vertex: " + line);
				faceVertices.push_back(idx - 1); // OBJ indices are 1-based
			}

			if (faceVertices.size() < 3)
				throw std::runtime_error("Face has fewer than 3 vertices: " + line);

			// Triangulate the polygon
			for (size_t i = 1; i < faceVertices.size() - 1; ++i)
			{
				obj.triangles.push_back(faceVertices[0]);
				obj.triangles.push_back(faceVertices[i]);
				obj.triangles.push_back(faceVertices[i + 1]);
			}
        }
		else if (prefix == "vt" || prefix == "vn" || prefix == "usemtl" || prefix == "mtllib")
		{
			std::cerr << "Warning: ignoring line: " << line << std::endl;
		}
        // ignore unsupported lines
    }

	if (temp_vertices.empty())
        throw std::runtime_error("No vertices found.");

    // ---- Centering the object ----
    float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;
    float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;

    for (auto& v : temp_vertices) {
        minX = std::min(minX, v[0]);
        minY = std::min(minY, v[1]);
        minZ = std::min(minZ, v[2]);
        maxX = std::max(maxX, v[0]);
        maxY = std::max(maxY, v[1]);
        maxZ = std::max(maxZ, v[2]);
    }

    float centerX = (minX + maxX) / 2.0f;
    float centerY = (minY + maxY) / 2.0f;
    float centerZ = (minZ + maxZ) / 2.0f;

    for (auto& v : temp_vertices) {
        obj.vertices.push_back(v[0] - centerX);
        obj.vertices.push_back(v[1] - centerY);
        obj.vertices.push_back(v[2] - centerZ);
    }

    return obj;
}
