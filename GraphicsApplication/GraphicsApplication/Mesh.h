#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>

namespace aie { class ShaderProgram; }

class Mesh
{
public: 

	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	// vertex struct containing position, normals and texture coordinates
	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
		glm::vec4 tangent;
	};

	// mesh initializer
	void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	// initialises using an (obj)ect file
	void initialiseFromFile(const char* filename);

	// initializes a quad shape
	void initialiseQuad();
	// the to screen function
	virtual void draw();

	void loadMaterial(const char* fileName);

	void applyMaterial(aie::ShaderProgram* shader);

	void calculateTangents(Vertex* vertices, unsigned int vertexCount, const std::vector<unsigned int>& indices);

protected:
	// total tris being created
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
	// vao -> Vertex Array Object - "...which acts as a sort of wrapper for a mesh, combining vbos andan  ibos", AIE: Graphics Rendering Geometry Tutorial
	// vbo -> Vertex Buffer Object
	// ibo -> Index Buffer Object

	glm::vec3 Ka; // ambient colour of the surface
	glm::vec3 Kd; // diffuse colour of the surface
	glm::vec3 Ks; // specular colour of the surface
	float specularPower; // tightness of specular highlights

	aie::Texture mapKd; // diffuse texture map
	aie::Texture mapKs; // specular texture map
	aie::Texture mapBump; // normal map
};



