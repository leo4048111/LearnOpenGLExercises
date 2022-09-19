#include "Shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& filepath) :
	_id(0)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX, FRAGMENT
	};

	std::ifstream ifs(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(ifs, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	GLuint vs = compileShader(GL_VERTEX_SHADER, ss[0].str());
	GLuint fs = compileShader(GL_FRAGMENT_SHADER, ss[1].str());
	_id = glCreateProgram();

	glAttachShader(_id, vs);
	glAttachShader(_id, fs);
	glLinkProgram(_id);
	glValidateProgram(_id);
	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader()
{
	glDeleteShader(_id);
}

void Shader::bind() const
{
	glUseProgram(_id);
}

void Shader::unBind() const
{
	glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniformMatrix4fv(const std::string& name, glm::mat4 mat)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::compileShader(GLenum type, const std::string& src)
{
	GLuint shader = glCreateShader(type);
	const char* source = src.c_str();
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(shader, length, &length, message);
		printf("%s\n", message);
		return 0;
	}

	return shader;
}

int Shader::getUniformLocation(const std::string& name)
{
	if (_uniformMap.find(name) != _uniformMap.end())
		return _uniformMap[name];

	int loc = glGetUniformLocation(_id, name.c_str());
	if (loc == -1) printf("Warning: Uniform %s doesn't exist!\n", name.c_str());
	_uniformMap[name] = loc;

	return loc;
}
