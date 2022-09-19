#pragma once

#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int _id;
	std::unordered_map<std::string, int> _uniformMap;
public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unBind() const;

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform3f(const std::string& name, float v0, float v1, float v2);
	void setUniformMatrix4fv(const std::string& name, glm::mat4 mat);
private:
	unsigned int compileShader(GLenum type, const std::string& src);
	int getUniformLocation(const std::string& name);

};