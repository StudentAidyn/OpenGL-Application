#include "glad.h"
#include "Camera.h"
#include "Application.h"


glm::mat4 Camera::getViewMatrix() {
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);
    glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
    return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjectionMatrix(float w, float h) {
    return glm::perspective(glm::pi<float>() * 0.25f,
        w / h,
        0.1f, 1000.f);
}

void Camera::update(float deltaTime, GLFWwindow* window) {
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);

    //calculate the forwards and right axes and up axis for the camera
    glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
    glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
    glm::vec3 up(0, 1, 0);

    // use WASD, ZX keys to move camera around
    if (glfwGetKey(window, GLFW_KEY_X))
        m_position += up * m_speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_Z))
        m_position -= up * m_speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_D))
        m_position += right * m_speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_A))
        m_position -= right * m_speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W))
        m_position += forward * m_speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_S))
        m_position -= forward * m_speed * deltaTime;

    glm::vec2 mouseDelta = Application::get()->getMouseDelta();

    const float turnSpeed = 0.1f;
    // if the right button is down, increment theta and phi
    if (glfwGetMouseButton(window, 1))
    {
        m_theta += turnSpeed * mouseDelta.x;
        m_phi -= turnSpeed * mouseDelta.y;
    }

}
