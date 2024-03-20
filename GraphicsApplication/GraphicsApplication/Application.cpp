#include "glad.h"
#include "Application.h"

Application::Application() {
    //if (s_instance = nullptr) {
    //    s_instance = this;
    //}
}

void Application::SetMousePosition(GLFWwindow* window, double x, double y)
{
    s_instance->m_mousePosition.x = (float)x;
    s_instance->m_mousePosition.y = (float)y;
}