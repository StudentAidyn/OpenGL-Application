#pragma once
#include "Application.h"
#include "Instance.h"

class Scene
{
public:
	Scene();
	~Scene();
	Scene(Camera* camera, glm::vec2 windowSize, Light& light, glm::vec3
		ambientLight);
	void AddInstance(Instance* instance);

protected:
	Camera* m_camera;
	glm::vec2 m_windowSize;
	Light m_light;
	glm::vec3 m_ambientLight;
	std::list<Instance*> m_instances;
};

