#include "Application3D.h"

bool Application3D::startup() {

    setBackgroundColour(0.25f, 0.25f, 0.25f);

    // initialise gizmo primitive counts
    Gizmos::create(10000, 10000, 10000, 10000);

    // create simple camera transforms
    m_view = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
    m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);

    m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
    m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

    if (m_shader.link() == false) {
        printf("Shader Error: %s\n", m_shader.getLastError());
        return false;
    }

    m_quadMesh.initialiseQuad();

    // make the quad 10 units wide
    m_quadTransform = {
          10,0,0,0,
          0,10,0,0,
          0,0,10,0,
          0,0,0,1 };

    return true;
}