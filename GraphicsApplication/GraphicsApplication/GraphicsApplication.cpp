#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>


const int windowWidth = 1280;
const int windowHeight = 720;
int main()
{
    if (glfwInit() == false) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Computer Graphics", nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }


    while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

        // our game logic and update code goes here!
        // so does our render code!

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

    // the rest of our code goes here!
    glfwTerminate();
    return 0;
}


