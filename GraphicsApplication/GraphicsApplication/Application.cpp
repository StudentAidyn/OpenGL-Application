#include "glad.h" //?
#include "Application.h"


Application::Application() {
    // upset but variables are set within startup :)
}

Application::~Application() {

}

bool Application::startup() {
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

    Gizmos::create(10000, 10000, 0, 0);

    m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
    m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

    glClearColor(m_backgroundColour.x, m_backgroundColour.y, m_backgroundColour.z, m_backgroundColour.w);
    glEnable(GL_DEPTH_TEST); // enables the depth buffer

    printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

    return true;
}

bool Application::update() {
    return (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}

void Application::draw() {
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

    /// IN THE TUTORIAL FOR GRAPHICS RENDERING GEOMETRY-
    /// IT STATES TO PLACE YOUR M_SHADER WITHIN APPLICATION3D BUT STATES TO PLACE IT WITHIN HERE?
    /// SOME INCONSISTENCIES TO LOOK THROUGH WITH SHANE NON-THE LESS


    //// bind shader
    //m_shader.bind();

    //// bind transform
    //auto pvm = m_projection * m_view * m_quadTransform;
    //m_shader.bindUniform("ProjectionViewModel", pvm);

    //// draw quad
    //m_quadMesh.draw();

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Application::shutdown() {


    Gizmos::destroy();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}