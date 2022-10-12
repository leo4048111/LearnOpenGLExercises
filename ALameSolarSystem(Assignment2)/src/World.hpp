#pragma once

#include "Planet.hpp"
#include "Helper.hpp"
#include "sdk/Shader.hpp"

typedef struct
{
	Planet* planet;
	std::string centerPlanet;
	float eccentricity;
	float focalDistance;
}PlanetInfo;

class World
{
	NONCOPYABLE(World)

public:
	World() = default;
	~World() = default;

	void init(int horizontalLevel, int verticalLevel, float radius);

	void addPlanet(std::string name, std::string centerPlanet, float eccentricity, float focalDistance, std::shared_ptr<Shader>& shader,
		float mass = 1.0f, glm::vec3 pos = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f }, glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

	void draw(GLenum mode = GL_FILL);

private:
	std::shared_ptr<VertexArray> _vaSphere;

	std::unordered_map<std::string, Planet*> _planetNameMap;

	std::vector<PlanetInfo> _planetInfos;
};

inline auto g_world = std::make_unique<World>();

void World::init(int horizontalLevel, int verticalLevel, float radius)
{
	_vaSphere = Helper::makeSphereVertexArray(horizontalLevel, verticalLevel, radius);
}

void World::addPlanet(std::string name, std::string centerPlanet, float eccentricity, float focalDistance, std::shared_ptr<Shader>& shader,
	float mass, glm::vec3 pos, glm::vec3 scale, glm::vec4 color)
{
	glm::vec3 center = { 0.0f, 0.0f, 0.0f };
	if (_planetNameMap.find(centerPlanet) != _planetNameMap.end()) center = _planetNameMap[centerPlanet]->position();
	Planet* planet = new Planet(_vaSphere, shader, mass, pos + center, scale, color);
	_planetNameMap.insert(std::make_pair(name, planet));
	_planetInfos.push_back({ planet, centerPlanet, eccentricity, focalDistance });
}

void World::draw(GLenum mode)
{
	for (auto& info : _planetInfos)
	{
		auto& planet = info.planet;
		if (_planetNameMap.find(info.centerPlanet) != _planetNameMap.end())
		{
			auto& centerPlanet = _planetNameMap[info.centerPlanet];
			planet->update(centerPlanet->position(), centerPlanet->mass(), info.eccentricity, info.focalDistance);
		}
	}

	for (auto& info : _planetInfos) info.planet->draw(mode);
}