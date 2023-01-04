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
    
    glfwSetFramebufferSizeCallback(m_instance, framebuffer_size_callback);
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

void Window::keyEvent(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        onKeyPress(key);
    }
    else if (action == GLFW_RELEASE)
    {
        onKeyRelease(key);
    }
    else if (action == GLFW_REPEAT)
    {
        onKeyHold(key);
    }
}

void Window::addKeyPressBinding(int key, const Callback callback)
{
    m_KeyPressCallbacks.insert({ key, callback });
}

void Window::addKeyReleaseBinding(int key, const Callback callback)
{
    m_KeyReleaseCallbacks.insert({key, callback});
}

void Window::addKeyHoldBinding(int key, const Callback callback)
{
    m_KeyHoldCallbacks.insert({ key, callback });
}

void Window::removeKeyPressBinding(int key)
{
    m_KeyPressCallbacks.erase(key);
}

void Window::removeKeyReleaseBinding(int key)
{
    m_KeyReleaseCallbacks.erase(key);
}

void Window::removeKeyHoldBinding(int key)
{
    m_KeyHoldCallbacks.erase(key);
}

void Window::swapKeyPressBinding(int formerKey, int newKey)
{
    Callback callback = m_KeyPressCallbacks.at(formerKey);
    removeKeyPressBinding(formerKey);
    addKeyPressBinding(newKey, callback);
}

void Window::swapKeyReleaseBinding(int formerKey, int newKey)
{
    Callback callback = m_KeyReleaseCallbacks.at(formerKey);
    removeKeyReleaseBinding(formerKey);
    addKeyReleaseBinding(newKey, callback);
}

void Window::swapKeyHoldBinding(int formerKey, int newKey)
{
    Callback callback = m_KeyHoldCallbacks.at(formerKey);
    removeKeyHoldBinding(formerKey);
    addKeyHoldBinding(newKey, callback);
}

void Window::onKeyPress(int key)
{
    m_KeyPressCallbacks[key];
}

void Window::onKeyRelease(int key)
{
    m_KeyReleaseCallbacks[key];
}

void Window::onKeyHold(int key)
{
    m_KeyHoldCallbacks[key];
}