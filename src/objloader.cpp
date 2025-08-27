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
	(void)path;
	Object3D object;

	// Mesh 1: red triangle
	Mesh mesh1;
	mesh1.vertices =
	{
		 0.232407,  1.119982,  1.133819,   1.0f, 0.0f, 0.0f,  // top red
		 0.232406,  1.119982,  1.602814,   1.0f, 0.0f, 0.0f,  // left red
		 0.232407, -0.294496,  2.297937,   1.0f, 0.0f, 0.0f   // right red
	};
	mesh1.textureID = 0;       // no texture for now
	mesh1.setup();
	object.meshes.push_back(std::move(mesh1));

	// Mesh 2: green triangle
	Mesh mesh2;
	mesh2.vertices = {
		-0.227403, 1.104268, 0.408501,    0.0f, 1.0f, 0.0f,
		-0.227403, 0.507336, 0.901477,   0.0f, 1.0f, 0.0f,
		 0.232406, -1.222569, 1.497195,   0.0f, 1.0f, 0.0f
	};
	mesh2.textureID = 0;
	mesh2.setup();
	object.meshes.push_back(std::move(mesh2));

	return object;
}

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
}
