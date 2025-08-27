#pragma once
#include <string>
#include "mesh.hpp"
#include <vector>

class Object3D
{
	public:
		std::vector<Mesh> meshes;       // one mesh per material/group
};

Object3D loadOBJ(const std::string& path);  // temporary version
