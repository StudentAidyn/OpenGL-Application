#pragma once

#include <glm/glm.hpp>

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
	};

	// mesh initializer
	void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	// initializes a quad shape
	void initialiseQuad();
	// the to screen function
	virtual void draw();

protected:
	// total tris being created
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
	// vao -> Vertex Array Object - "...which acts as a sort of wrapper for a mesh, combining vbos andan  ibos", AIE: Graphics Rendering Geometry Tutorial
	// vbo -> Vertex Buffer Object
	// ibo -> Index Buffer Object

};



