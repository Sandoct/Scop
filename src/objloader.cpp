#include "objloader.hpp"

void loadMTL(const std::string& mtlPath, Object3D& obj)
{
	std::ifstream file("resources/"+mtlPath);
	if (!file.is_open())
	{
		std::cerr << "Could not open MTL file: " << mtlPath << std::endl;
		return;
	}

	std::string line;
	Material mat;
	bool hasMat = false;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string tag;
		iss >> tag;

		if (tag == "newmtl")
		{
			if (hasMat)
				obj.materials[mat.name] = mat;
			iss >> mat.name;
			hasMat = true;
		}
		else if (tag == "Ka")
		{
			iss >> mat.Ka[0] >> mat.Ka[1] >> mat.Ka[2];
		}
		else if (tag == "Kd")
		{
			iss >> mat.Kd[0] >> mat.Kd[1] >> mat.Kd[2];
		}
		else if (tag == "Ks")
		{
			iss >> mat.Ks[0] >> mat.Ks[1] >> mat.Ks[2];
		}
		else if (tag == "Ns")
		{
			iss >> mat.Ns;
		}
		else if (tag == "Ni")
		{
			iss >> mat.Ni;
		}
		else if (tag == "Tr" || tag == "d")
		{
			iss >> mat.Ni;
		}
		else if (tag == "illum")
		{
			iss >> mat.illum;
		}
	}
	if (hasMat)
		obj.materials[mat.name] = mat;
}


Object3D loadOBJ(const std::string& path)
{
    std::ifstream file(path);
    if (path == "" || !file.is_open())
        throw std::runtime_error("Could not open file");

    Object3D obj;
	Material defaultMat;
	defaultMat.Kd = {0.0f, 0.5f, 0.0f};
	obj.materials["__default"] = defaultMat;
	obj.currentMaterial = "__default";
    std::vector<std::array<float,3>> temp_vertices;
    std::string line;

    // --- Load vertices ---
    while (std::getline(file, line))
	{
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "mtllib")
		{
			std::string mtlPath;
			ss >> mtlPath;
			loadMTL(mtlPath, obj);
		}
		else if (prefix == "v")
		{
            float x,y,z;
            if (!(ss >> x >> y >> z))
                throw std::runtime_error("Invalid vertex line: " + line);
            temp_vertices.push_back({x,y,z});
        }
		else if (prefix == "usemtl")
		{
			std::string matName;
			ss >> matName;

			if (!obj.materials.empty() && obj.materials.find(matName) != obj.materials.end())
				obj.currentMaterial = matName;
			else
			{
				std::cerr << "Warning: material \"" << matName << "\" not found. Using default." << std::endl;
				obj.currentMaterial = "__default";
			}
		}
        else if (prefix == "f")
		{
            std::vector<unsigned int> faceVertices;
            unsigned int idx;

            while (ss >> idx) {
                if (idx == 0 || idx > temp_vertices.size())
                    throw std::runtime_error("Face references non-existent vertex: " + line);
                faceVertices.push_back(idx-1);
            }

            if (faceVertices.size() < 3)
                throw std::runtime_error("Face has fewer than 3 vertices: " + line);

            // Triangulate polygon
            for (size_t i=1; i<faceVertices.size()-1; ++i) {

                unsigned int i0 = faceVertices[0];
                unsigned int i1 = faceVertices[i];
                unsigned int i2 = faceVertices[i+1];

                // Copy positions (flat triangles)
                for (unsigned int vi : {i0, i1, i2}) {
                    obj.vertices.push_back(temp_vertices[vi][0]);
                    obj.vertices.push_back(temp_vertices[vi][1]);
                    obj.vertices.push_back(temp_vertices[vi][2]);
                }

                // Assign a single random color per triangle
                float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                for (int j=0;j<3;j++) {
                    obj.defaultColors.push_back(r);
                    obj.defaultColors.push_back(g);
                    obj.defaultColors.push_back(b);
                }

				Material& mat = obj.materials[obj.currentMaterial];
				for (int j = 0; j < 3; j++)
				{
					obj.materialColors.push_back(mat.Kd[0]);
					obj.materialColors.push_back(mat.Kd[1]);
					obj.materialColors.push_back(mat.Kd[2]);
				}

                // Flat indices
                unsigned int base = obj.vertices.size()/3 - 3;
                obj.triangles.push_back(base+0);
                obj.triangles.push_back(base+1);
                obj.triangles.push_back(base+2);

                // Placeholder UVs (optional for future texture)
                // obj.uvs.push_back(...);
            }
        }
        else if (prefix == "vt" || prefix == "vn")
		{
            std::cerr << "Warning: ignoring line: " << line << std::endl;
        }
    }

    if (temp_vertices.empty())
        throw std::runtime_error("No vertices found.");

    // --- Center object ---
    float minX=FLT_MAX, minY=FLT_MAX, minZ=FLT_MAX;
    float maxX=-FLT_MAX, maxY=-FLT_MAX, maxZ=-FLT_MAX;
    for (auto &v : temp_vertices) {
        minX = std::min(minX, v[0]); minY = std::min(minY, v[1]); minZ = std::min(minZ, v[2]);
        maxX = std::max(maxX, v[0]); maxY = std::max(maxY, v[1]); maxZ = std::max(maxZ, v[2]);
    }
    float centerX = (minX+maxX)/2.0f;
    float centerY = (minY+maxY)/2.0f;
    float centerZ = (minZ+maxZ)/2.0f;

    for (size_t i=0;i<obj.vertices.size();i+=3) {
        obj.vertices[i+0] -= centerX;
        obj.vertices[i+1] -= centerY;
        obj.vertices[i+2] -= centerZ;
    }

    return obj;
}
