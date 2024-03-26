#include "glad.h"
#include "Application3D.h"
#include "imgui_glfw3.h"
#include "Instance.h"

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

	// initialize the GUI components
	aie::ImGui_Init(m_window, true);

	s_instance = this;
	glfwSetCursorPosCallback(m_window, &Application::SetMousePosition);

	glClearColor(m_backgroundColour.x, m_backgroundColour.y, m_backgroundColour.z, m_backgroundColour.w);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalmap.frag");

	if (m_phongShader.link() == false) {
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}


	m_altMesh.initialiseFromFile("../models/soulspear/soulspear.obj");
	m_altMesh.loadMaterial("../models/soulspear/soulspear.mtl");

	glm::mat4 altTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};



	m_light.colour = { 1,1,1 };
	m_light.direction = vec3(1, -1, 1);
	// remove ambient light

	m_scene = new Scene(&m_camera, glm::vec2(getWindowWidth(), getWindowHeight()), m_light, glm::vec3(0.25f, 0.25f, 0.25f));
	m_scene->AddInstance(new Instance(altTransform, &m_altMesh, &m_phongShader));

	// red light on the left
	m_scene->getPointLights().push_back(Light(vec3(5, 3, 0), vec3(1, 0, 0), 50));
	// green light on the right
	m_scene->getPointLights().push_back(Light(vec3(-5, 3, 0), vec3(0, 1, 0), 50));



    return true;
}

bool Application3D::update() {

	aie::ImGui_NewFrame();

	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Sunlight Direction", &m_light.direction[0], 0.1f, -1.0f, 1.0f);
	m_scene->setLightDirection(m_light.direction);
	ImGui::DragFloat3("Sunlight Colour", & m_light.colour[0], 0.1f, 0.0f, 2.0f);
	m_scene->setLightColour(m_light.colour);
	ImGui::End();
	
	m_camera.update(0.1f, m_window); // delta time, current window

	m_lastMousePosition = m_mousePosition;

    return (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}

void Application3D::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1));

	glm::mat4 pv = m_camera.getProjectionMatrix(getWindowWidth(), getWindowHeight()) * m_camera.getViewMatrix();

	m_scene->draw();

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

	// render the GUI last so it overlays
	ImGui::Render();

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Application3D::shutdown() {
	aie::ImGui_Shutdown();
	Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
	// deleting the scene
	delete m_scene;
	m_scene = nullptr;
}







