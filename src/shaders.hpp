#ifndef SHADERS_HPP
#define SHADERS_HPP

#pragma once
#include <GL/glew.h>

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use() const;
};

#endif
