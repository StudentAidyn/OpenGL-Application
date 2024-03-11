#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>

#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;



class Application
{
public:
    Application();
    ~Application();
    bool startup();
    bool update();
    void draw();
    void shutdown();

    void setBackgroundColour(float r, float g, float b) { m_backgroundColour = vec4(r, g, b, 1); }
    int getWindowWidth() { return m_windowWidth; }
    int getWindowHeight() { return m_windowHeight; }

protected:
    glm::mat4 m_view;
    glm::mat4 m_projection;

    GLFWwindow* m_window;
    vec4 m_backgroundColour = vec4(0.25f, 0.25f, 0.25f, 1);
    const int m_windowWidth = 1280;
    const int m_windowHeight = 720;
};



//

//

//}
//
