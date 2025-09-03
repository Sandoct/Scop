#pragma once
#include <string>
#include "mesh.hpp"
#include <vector>

class Object3D
{
	public:
		std::vector<float>		vertices;
		std::vector<unsigned int>	triangles;
};

Object3D loadOBJ(const std::string& path);  // temporary version
