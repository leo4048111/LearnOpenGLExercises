#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

inline bool glLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		printf("[OpenGL Error] (0x%x): %s %s:%d\n", error, function, file, line);
		return false;
	}

	return true;
}

inline void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) \
glClearError(); \
x; \
ASSERT(glLogCall(#x, __FILE__, __LINE__));