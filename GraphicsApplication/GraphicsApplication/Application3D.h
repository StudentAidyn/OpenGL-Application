#pragma once
#include "glad.h"
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"

class Application3D : public Application {
public:

    Application3D();
    virtual ~Application3D();

    virtual bool startup();
    virtual void shutdown();

    virtual void update(float deltaTime);
    virtual void draw();

protected:

    glm::mat4   m_viewMatrix;
    glm::mat4   m_projectionMatrix;

    aie::ShaderProgram   m_shader;
    Mesh    m_quadMesh;
    glm::mat4   m_quadTransform;
};

