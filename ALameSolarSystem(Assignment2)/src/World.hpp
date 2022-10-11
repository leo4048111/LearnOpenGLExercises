#pragma once

#include "Planet.hpp"
#include "sdk/Camera.hpp"
#include "sdk/Controller.hpp"
#include "sdk/Shader.hpp"

class World
{
	NONCOPYABLE(World)

public:
	World(GLFWwindow* window, Camera& camera);
	~World();

	void addPlanet(glm::vec4 color, glm::vec3 scale, float speed, std::shared_ptr<Shader>& shader);

private:
	Camera _camera;
	GLFWwindow* _window;
};

inline auto g_world = std::make_unique<World>();

World::World(GLFWwindow* window, Camera& camera):
	_camera(camera), _window(window)
{
	Controller::getInstance()->install(window, &_camera);
}

World::~World()
{
	Controller::getInstance()->uninstall();
}