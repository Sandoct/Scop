#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cfloat>
#include <iostream>
#include <cstdlib>
#include <GL/glew.h>

struct Material {
    std::string name;
	std::array<float, 3>	Ka; // ambient
	std::array<float, 3>	Kd; // diffuse
	std::array<float, 3>	Ks; // specular
	float	Ns;    // shininess
	float	Ni;    // shininess
	float	Tr;    // transparency
	int		illum;

	std::string map_Kd;
    GLuint textureID = 0;
};

class Object3D
{
	public:
		std::vector<float>		vertices;
		std::vector<float>		texCoords;
		std::vector<float>		defaultColors;
		std::vector<float>		materialColors;
		std::vector<unsigned int>	triangles;

		std::map<std::string, Material> materials;
		std::string currentMaterial;
};

Object3D loadOBJ(const std::string& path);
