#include "glad.h"
#include "Application3D.h"

Application3D::Application3D() {
	m_shader = new aie::ShaderProgram;
}

Application3D::~Application3D() {
	delete m_shader;
	m_shader = nullptr;
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

	m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	glClearColor(m_backgroundColour.x, m_backgroundColour.y, m_backgroundColour.z, m_backgroundColour.w);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

    m_shader->loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
    m_shader->loadShader(aie::eShaderStage::FRAGMENT, "../bin/shaders/simple.frag");

    if (m_shader->link() == false) {
        printf("Shader Error: %s\n", m_shader->getLastError());
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

//bool Application3D::startup()
//{
//	setBackgroundColour(0.25f, 0.25f, 0.25f);
//
//
//#pragma region Added in from Application.cpp
//
//
//	/// Initialize GLFW
//	if (glfwInit() == false)
//	{
//		return -1;
//	}
//
//	/// Create a window
//	m_window = glfwCreateWindow(getWindowWidth(), getWindowWidth(), "Computer Graphics", nullptr, nullptr);
//
//	/// Check if the window was created
//	if (m_window == nullptr)
//	{
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(m_window);
//
//	if (!gladLoadGL())
//	{
//		glfwDestroyWindow(m_window);
//		glfwTerminate();
//		return -3;
//	}
//
//#pragma endregion
//
//
//
//	/// initialize gizmo primitive counts
//	Gizmos::create(10000, 10000, 10000, 10000);
//
//	/// set up the camera
//	m_view = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
//	m_projection = glm::perspective(glm::pi<float>() * 0.25f, (float)(getWindowWidth() / getWindowHeight()), 0.1f, 1000.f);
//
//	m_shader->loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
//	m_shader->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
//
//	if (m_shader->link() == false)
//	{
//		printf("Shader Error: %s\n", m_shader->getLastError());
//		return false;
//	}
//
//	//m_quadMesh.initialiseQuad();
//
//	///make the quad 10 units wide
//	m_quadTransform = {
//		10,0, 0, 0,
//		0, 10, 0, 0,
//		0, 0, 10, 0,
//		0, 0, 0, 1
//	};
//
//
//	// define 6 vertices for 2 triangles
//	/*Mesh::Vertex vertices[6];
//	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
//	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
//	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
//
//	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
//	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
//	vertices[5].position = { 0.5f, 0, -0.5f, 1 };*/
//
//
//
//	//m_quadMesh.initialise(6, vertices);
//
//
//	// define 4 vertices for 2 triangles
//	Mesh::Vertex vertices[4];
//	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
//	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
//	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
//	vertices[3].position = { 0.5f, 0, -0.5f, 1 };
//
//	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
//
//	//m_quadMesh.initialise(4, vertices, 6, indices);
//
//
//	return true;
//}

bool Application3D::update() {
    return (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}

void Application3D::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1));

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

	Gizmos::draw(m_projection * m_view);


	// bind shader
	m_shader->bind();

	// bind transform
	auto pvm = m_projection * m_view * m_quadTransform;
	m_shader->bindUniform("ProjectionViewModel", pvm);

	// draw quad
	m_quadMesh.draw();

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Application3D::shutdown() {
	Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}