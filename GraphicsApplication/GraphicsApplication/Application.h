#pragma once

#include <GLFW/glfw3.h>

#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"

#include "Mesh.h"
#include "Shader.h"
#include "Scene.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;

class Application
{
public:
    Application();
    ~Application() {};

    /// Sets up the render scene
    virtual bool startup() = 0;
    /// Call to update, is called every available frame
    virtual bool update() = 0;
    /// Draws all the objects and meshes to the scene
    virtual void draw() = 0;
    /// Closes all pipeline components and unbinds.
    virtual void shutdown() = 0;

    void setBackgroundColour(float r, float g, float b) { m_backgroundColour = vec4(r, g, b, 1); }
    int getWindowWidth() { return m_windowWidth; }
    int getWindowHeight() { return m_windowHeight; }

    /// singleton of Application
    static Application* get() { return s_instance; }

    glm::vec2 getMousePosition() { return m_mousePosition; }
    glm::vec2 getMouseDelta() { return m_mousePosition - m_lastMousePosition; }

    /// Set up mouse input
    static void SetMousePosition(GLFWwindow* window, double x, double y);



protected:
    /// Singleton instance of the Application Class
    static Application* s_instance;

    // can possibly get rid of this
    glm::mat4 m_view;
    glm::mat4 m_projection;

    /// window pointer reference
    GLFWwindow* m_window;
    /// background colour container
    vec4 m_backgroundColour = vec4(0.25f, 0.25f, 0.25f, 1);
    /// window width in pixels
    const int m_windowWidth = 1280;
    /// windo height in pixels
    const int m_windowHeight = 720;

    /// the current position of the mouse
    glm::vec2 m_mousePosition;
    /// the last position of the mouse, us set at the end of the update call
    glm::vec2 m_lastMousePosition;

    Light m_light;
    glm::vec3 m_ambientLight;

    /// camera reference
    Camera m_camera;
};


