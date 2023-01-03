#include "Window.h"

Window::Window()
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
    m_instance = glfwCreateWindow(m_SCREEN_WIDTH, m_SCREEN_HEIGHT, "Window Title", monitorWindow, NULL);
    if (m_instance == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_instance);

    glfwSetWindowUserPointer(m_instance, this);
    
    glfwSetKeyCallback(m_instance, keyEventCallback);
}

Window::~Window()
{
    
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::keyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    instance->keyEvent(key, action);
}

void Window::addBinding(int key, const Callback callback)
{
    m_Callbacks.insert({ key, callback });
}

void Window::removeBinding(int key)
{
    m_Callbacks.erase(key);
}

void Window::swapBinding(int formerKey, int newKey)
{
    Callback callback = m_Callbacks.at(formerKey);
    removeBinding(formerKey);
    addBinding(newKey, callback);
}

void Window::keyEvent(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        onKeyPress(key);
    }
}

void Window::onKeyPress(int key)
{
    
}

void Window::onKeyRelease(int key)
{

}

void Window::onKeyHold(int key)
{

}