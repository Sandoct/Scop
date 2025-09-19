#ifndef SHADERS_HPP
#define SHADERS_HPP

#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use() const;

	// Helper uniform setters
	void setInt(const std::string& name, int value) const;
	void setBool(const std::string& name, bool value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const float* mat) const;
};

#endif
