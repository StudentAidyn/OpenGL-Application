#pragma once
//#include "glad.h"
#include "Application.h"


class Application3D : public Application {
public:

    Application3D();
    ~Application3D();

    bool startup() override;
    void shutdown() override;

    bool update() override;
    void draw()override;

protected:

    aie::ShaderProgram* m_shader;
    Mesh    m_quadMesh;
    // controls the TRNASFORMS of the mesh (position, size, rotation, __ ?)
    glm::mat4   m_quadTransform;

};

