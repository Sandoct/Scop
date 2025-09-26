#include "shaders.hpp"

// Vertex Shader source
const char* getVertexShaderSource()
{
	return R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	layout (location = 2) in vec2 aTexCoord;

	out vec3 FragColorIn;
	out vec2 TexCoord;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		FragColorIn = aColor;
		TexCoord = aTexCoord;
		gl_Position = projection * view * model * vec4(aPos, 1.0);
	}
	)";
}
// Fragment Shader source
const char* getFragmentShaderSource()
{
	return R"(
	#version 330 core
	in vec3 FragColorIn;
	in vec2 TexCoord;

	uniform bool useTexture;
	uniform sampler2D texture1;

	out vec4 FragColor;

	void main()
	{
		vec4 texColor = texture(texture1, TexCoord);
		vec4 finalColor = useTexture ? texColor : vec4(FragColorIn, 1.0);
		FragColor = finalColor;
	}
	)";
}

Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const float* mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat);
}
