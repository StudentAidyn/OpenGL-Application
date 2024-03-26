#pragma once
#include <iostream>
#include <list>
#include "Camera.h"
#include <vector>

class Instance;


struct Light {
	glm::vec3 direction;
	glm::vec3 colour;
	Light() { direction = glm::vec3(0); colour = glm::vec3(1); }
	Light(glm::vec3 pos, glm::vec3 col, float intensity) {
		direction = pos;
		colour = col * intensity;
	}
};

class Scene
{
public:
	Scene() {};
	~Scene();
	// passing in light reference but in tutorial in app3d it is not a pointer
	Scene(Camera* camera, glm::vec2 windowSize, Light& light, glm::vec3 ambientLight);
	void AddInstance(Instance* instance);

	void draw();

	Camera* getCamera() { return m_camera; }
	glm::vec2 getWindowSize() { return m_windowSize; }
	glm::vec3 getAmbientLight() { return m_ambientLight; }
	Light getLight() { return m_sunLight; }

	void setLightDirection(glm::vec3 lDir) { m_sunLight.direction = { lDir }; }
	void setLightColour(glm::vec3 lCol) { m_sunLight.colour = { lCol }; }

	int getNumLights() { return (int)m_pointLights.size(); }

	glm::vec3* getPointLightPositions() { return &m_pointLightPositions[0]; }
	glm::vec3* getPointLightColours() { return &m_pointLightColours[0]; }

	std::vector<Light>& getPointLights() { return m_pointLights; }


protected:
	Camera* m_camera;
	glm::vec2 m_windowSize;

	static const int MAX_LIGHTS = 4;
	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColours[MAX_LIGHTS];

	Light m_sunLight;
	std::vector<Light> m_pointLights;
	glm::vec3 m_ambientLight;
	std::list<Instance*> m_instances;
};

