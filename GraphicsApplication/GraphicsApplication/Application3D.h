#pragma once
//#include "glad.h"
#include "Application.h"
#include "Shader.h"


class Application3D : public Application {
public:

    Application3D();
    ~Application3D();

    bool startup() override;
    void shutdown() override;

    bool update() override;
    void draw()override;

protected:

    aie::ShaderProgram m_shader;
    aie::ShaderProgram m_phongShader;

    Mesh    m_quadMesh;
    // controls the TRANSFORMS of the mesh (position, size, rotation, __ ?)
    glm::mat4   m_quadTransform;

    Mesh m_bunnyMesh;
    glm::mat4 m_bunnyTransform;

    struct Light {
        glm::vec3 direction;
        glm::vec3 colour;
    };

    Light m_light;
    glm::vec3 m_ambientLight;
};

