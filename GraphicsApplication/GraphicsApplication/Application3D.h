#pragma once
//#include "glad.h"
#include "Application.h"
#include "Shader.h"
#include "Texture.h"


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
    aie::ShaderProgram m_normalMapShader;

    aie::Texture m_gridTexture;
    // Mesh Object
    Mesh    m_quadMesh;
    // controls the TRANSFORMS of the mesh (position, size, rotation, ?SCALE? ?)
    glm::mat4   m_quadTransform;

    aie::Texture m_altTexture;
    Mesh m_altMesh;
    glm::mat4 m_altTransform;

    struct Light {
        glm::vec3 direction;
        glm::vec3 colour;
    };

    Light m_light;
    glm::vec3 m_ambientLight;
};

