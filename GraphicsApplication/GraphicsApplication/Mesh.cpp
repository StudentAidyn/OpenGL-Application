#include "glad.h"
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <vector>
//#include "gl_core_4_4.h" <- delete this >:(



Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad(){
    // check if mesh is not initialized already
    assert(vao == 0);

    // generate buffers
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);


    // bind vertex array aka a mesh wrapper
    glBindVertexArray(vao);

    // bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // define 6 vertices for 2 triangles
    Vertex vertices[6];
    vertices[0].position = { -0.5f, 0, 0.5f, 1 };
    vertices[1].position = { 0.5f, 0, 0.5f, 1 };
    vertices[2].position = { -0.5f, 0, -0.5f, 1 };

    vertices[3].position = { -0.5f, 0, -0.5f, 1 };
    vertices[4].position = { 0.5f, 0, 0.5f, 1 };
    vertices[5].position = { 0.5f, 0, -0.5f, 1 };

    // fill vertex buffer with defined verticies with the size of a vertex in bytes
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    // enable first element as position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // quad has 2 triangles
    triCount = 2;
}


// Mesh Initialiser
void Mesh::initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount /* = 0*/, unsigned int* indices /*= nullptr*/) {
    assert(vao == 0);

    // generate buffers for vertex buffer object and vertex array object
    glGenBuffers(1, &vbo); // vertex BUFFER object
    glGenVertexArrays(1, &vao); // vertex ARRAY object

    // bind vertex array (a mesh wrapper)
    glBindVertexArray(vao);


    /*  glBindBuffer assigns an unsigned int to the buffer then
        glBufferData assigns the data into the corresponding buffer 
        
        the buffers use the reference of GL_ARRAY_BUFFER OR GL_ELEMENT_ARRAY_BUFFER */

    // bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    // fill vertex buffer
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);


    // enabling first element as position
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);


    // check for indicies and bind indices if there are any
    if (indexCount != 0) { // indexCount is an unsigned int (uint) there for it does not need a greater than check
        glGenBuffers(1, &ibo);

        // bind vertex buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        // fill vertex buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        triCount = indexCount / 3;
    }
    else {
        triCount = vertexCount / 3;
    }

    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// mesh initialiser that takes a file name, it uses .[obj]ect files
void Mesh::initialiseFromFile(const char* filename)
{
    // read vertices from the model
    const aiScene* scene = aiImportFile(filename, 0);
    // just use the first mesh we find for now
    aiMesh* mesh = scene->mMeshes[0];


    // extract indicies from the first mesh
    int numFaces = mesh->mNumFaces;
    std::vector<unsigned int> indices;
    for (int i = 0; i < numFaces; i++)
    {
        // uses the array within aiMesh an outsourced library that can handle elements of rendering.
        indices.push_back(mesh->mFaces[i].mIndices[0]);
        indices.push_back(mesh->mFaces[i].mIndices[2]);
        indices.push_back(mesh->mFaces[i].mIndices[1]);
        // generate a second triangle for quads
        if (mesh->mFaces[i].mNumIndices == 4)
        {
            indices.push_back(mesh->mFaces[i].mIndices[0]);
            indices.push_back(mesh->mFaces[i].mIndices[3]);
            indices.push_back(mesh->mFaces[i].mIndices[2]);
        }
    }

    // extract vertex data
    int numV = mesh->mNumVertices;
    Vertex* vertices = new Vertex[numV];
    for (int i = 0; i < numV; i++)
    {
        vertices[i].position = glm::vec4(mesh->mVertices[i].x,
            mesh->mVertices[i].y, mesh->mVertices[i].z, 1);
        // TODO, normals and UVs
    }
    // calls the mesh initialiser passing in the vertices and indices found
    initialise(numV, vertices, indices.size(), indices.data());
    delete[] vertices;
}

void Mesh::draw() {
    glBindVertexArray(vao);
    // using indices or just vertices?
    if (ibo != 0)
        glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}