#pragma once

#include "sdk/VertexArray.hpp"
#include "sdk/Shader.hpp"

class Planet
{
private:
	std::shared_ptr<VertexArray> _sphereVA;
	Shader& shader

	Planet(std::shared_ptr<VertexArray>& va, Shader& shader):
		_sphereVA(va), 
	{

	}
};