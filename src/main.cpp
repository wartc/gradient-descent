#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Grid.h"
#include "Shader.h"

constexpr float ASPECT_RATIO = 16.f / 9;
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = WINDOW_WIDTH / ASPECT_RATIO;

void windowSizeCallback(GLFWwindow* window, int width, int height) {
    // g_camera.setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
    glViewport(0, 0, width, height);
}

bool g_wireframeActive = false;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_X) {
        if (g_wireframeActive)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        g_wireframeActive = !g_wireframeActive;
    } else if (action == GLFW_PRESS && (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Gradient Descent", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << '\n';

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load GLAD" << '\n';
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera cam({-1.0f, 2.0f, 4.0f});
    // cam.look({1.0f, 1.0f, 1.0f});

    Grid g;

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        g.render(cam);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
