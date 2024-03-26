#pragma once
#include "Shader.h"
class Scene;
class Mesh;


class Instance
{
public:
	Instance() {};
	Instance(glm::mat4 transform, Mesh* mesh, aie::ShaderProgram* shader);
	~Instance();


	void draw(Scene* scene);
	glm::mat4 makeTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);

protected:
	glm::mat4 m_transform;
	Mesh* m_mesh;
	aie::ShaderProgram* m_shader;
};

