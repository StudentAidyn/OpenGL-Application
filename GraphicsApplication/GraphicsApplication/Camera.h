#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera() {}
	~Camera() {}

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float w, float h);

	/// Camera update function, changes the current "position" and "orientation" of the camera
	void update(float deltaTime, GLFWwindow* window);
	glm::vec3 getPosition() { return glm::vec3(glm::inverse(getViewMatrix())[3]); }

private:
	/// Theta is the orientation across the x-axis
	float m_theta;
	/// Phi is the orientation across the y-axis
	float m_phi;
	/// the current position of the camera
	glm::vec3 m_position;

	float m_speed = 0.1f;
};

