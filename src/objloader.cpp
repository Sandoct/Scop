#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include "mesh.hpp"
#include "objloader.hpp"

// Temporary OBJ loader — just returns multiple simple triangles
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

/*
// Parse the obj file into tirangle of vertex
Mesh parseOBJ(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filepath << "\n";
        return Mesh();
    }

    std::vector<Vec3> temp_vertices;
    std::vector<float> final_vertices;

    std::string line;
    std::regex vertex_regex(R"(v\s+([-\d.e]+)\s+([-\d.e]+)\s+([-\d.e]+))");
    std::regex face_regex(R"(f\s+(\d+)\s+(\d+)\s+(\d+)(?:\s+(\d+))?)");
    // captures either 3 or 4 vertex indices

    while (std::getline(file, line)) {
        std::smatch match;

        // Vertex line: v x y z
        if (std::regex_match(line, match, vertex_regex)) {
            float x = std::stof(match[1]);
            float y = std::stof(match[2]);
            float z = std::stof(match[3]);
            temp_vertices.push_back({x, y, z});
        }

        // Face line: f i j k or f i j k l
        else if (std::regex_match(line, match, face_regex)) {
            int i = std::stoi(match[1]) - 1;
            int j = std::stoi(match[2]) - 1;
            int k = std::stoi(match[3]) - 1;

            // Triangle 1
            for (int idx : {i, j, k}) {
                final_vertices.push_back(temp_vertices[idx].x);
                final_vertices.push_back(temp_vertices[idx].y);
                final_vertices.push_back(temp_vertices[idx].z);
            }

            // Check if quad (4th vertex exists)
            if (match[4].matched) {
                int l = std::stoi(match[4]) - 1;
                // Triangle 2: i, k, l
                for (int idx : {i, k, l}) {
                    final_vertices.push_back(temp_vertices[idx].x);
                    final_vertices.push_back(temp_vertices[idx].y);
                    final_vertices.push_back(temp_vertices[idx].z);
                }
            }
        }
    }

    Mesh mesh(final_vertices);
    mesh.setup();
    return mesh;
}*/
