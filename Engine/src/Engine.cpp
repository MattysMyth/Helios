#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	initGLFW();
	initGLAD();
}

Engine::~Engine()
{

}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool Engine::initGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitorWindow = NULL;
    if (!m_windowedMode)
    {
        monitorWindow = glfwGetPrimaryMonitor();
        const GLFWvidmode* monitorMode = glfwGetVideoMode(monitorWindow);
        m_SCREEN_WIDTH = monitorMode->width;
        m_SCREEN_HEIGHT = monitorMode->height;
    }

    // Initialise a window, throw an error if window failed to initialise
    m_window = glfwCreateWindow(m_SCREEN_WIDTH, m_SCREEN_HEIGHT, "Window Title", monitorWindow, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);

    // Set what function to call when the window is resized, passed as a parameter
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // Set framerate
    glfwSwapInterval(10);

    return true;
}

bool Engine::initGLAD()
{
    // Initialise GLAD, throw an error if GLAD failed to initialise
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

bool Engine::createVertexArray()
{
    return false;
}

bool Engine::createVertexBuffer()
{
    return false;
}

bool Engine::createIndexBuffer()
{
    return false;
}

bool Engine::createShader()
{
    return false;
}

void Engine::testPrint()
{
	std::cout << "Hello World" << std::endl;
}