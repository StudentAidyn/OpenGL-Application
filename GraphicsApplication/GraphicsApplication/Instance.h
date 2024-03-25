#pragma once

class Instance
{
public:
	Instance();
	~Instance();


	void draw();

protected:
	glm::mat4 m_transform;
	Mesh* m_mesh;
	aie::ShaderProgram* m_shader;
};

