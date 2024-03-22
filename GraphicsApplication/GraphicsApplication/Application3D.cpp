#include "glad.h"
#include "Application3D.h"
Application* Application::s_instance = nullptr;

Application3D::Application3D() {
}

Application3D::~Application3D() {
}

bool Application3D::startup() {

	// Checks if GLFW initializes correctly
	if (glfwInit() == false) {
		printf("GLFW failed to initialize");
		return false;
	}

	// creates new window setting it to the window global variable
	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "EPIC GRAPHICS MACHINE :D", nullptr, nullptr);

	// 
	if (m_window == nullptr) {
		glfwTerminate();
		printf("WINDOW failed to initialize");
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGL()) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		printf("GLADLOAD failed to initialize");
		return false;
	}

	Gizmos::create(10000, 10000, 1000, 0);

	s_instance = this;
	glfwSetCursorPosCallback(m_window, &Application::SetMousePosition);

	glClearColor(m_backgroundColour.x, m_backgroundColour.y, m_backgroundColour.z, m_backgroundColour.w);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

 //   m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
 //   m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	//if (m_shader.link() == false) {
	//	printf("Shader Error: %s\n", m_shader.getLastError());
	//	return false;
	//}

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (m_phongShader.link() == false) {
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	m_quadMesh.initialiseFromFile("../models/Owls.obj");
	m_quadMesh.loadMaterial("../models/Buddha.mtl");
	//m_quadMesh.initialiseQuad();	

    // make the quad 10 units wide
    m_quadTransform = {
          1,0,0,0,
          0,1,0,0,
          0,0,1,0,
          0,0,0,1 };

	m_light.colour = { 1,1,1 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };


    return true;
}


bool Application3D::update() {



	m_camera.update(0.1f, m_window);

	m_lastMousePosition = m_mousePosition;

	// query time since application started
	float time = glfwGetTime();
	// rotate light
	m_light.direction = glm::normalize(vec3(glm::cos(time * 2),
		glm::sin(time * 1.5f), 0));

    return (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}

void Application3D::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1));



	glm::mat4 pv = m_camera.getProjectionMatrix(getWindowWidth(), getWindowHeight()) * m_camera.getViewMatrix();

	//m_shader.bind();

	//// bind transform
	//auto pvm = pv * m_quadTransform;
	//m_shader.bindUniform("ProjectionViewModel", pvm);



	// bind shader
	m_phongShader.bind();

	// bind light
	m_phongShader.bindUniform("AmbientColour", m_ambientLight);
	m_phongShader.bindUniform("LightColour", m_light.colour);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	m_phongShader.bindUniform("cameraPosition", vec3(glm::inverse(m_camera.getViewMatrix())[3]));
	
	// bind transform
	auto pvm = pv * m_quadTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	m_phongShader.bindUniform("ModelMatrix", m_quadTransform);

	m_quadMesh.applyMaterial(&m_phongShader);

	// draw quad
	m_quadMesh.draw();

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	Gizmos::draw(pv);

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Application3D::shutdown() {
	Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}