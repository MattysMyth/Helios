#include "Window.h"

Helios::Window::Window()
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
    m_GLFWinstance = glfwCreateWindow(m_SCREEN_WIDTH, m_SCREEN_HEIGHT, "Window Title", monitorWindow, NULL);
    if (m_GLFWinstance == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_GLFWinstance);

    glfwSetWindowUserPointer(m_GLFWinstance, this);
    
    glfwSetFramebufferSizeCallback(m_GLFWinstance, framebuffer_size_callback);
    glfwSetKeyCallback(m_GLFWinstance, keyEventCallback);

    Helios::Input::addKeyPressBinding(this, GLFW_KEY_ESCAPE, [this]() {Helios::Input::defaultEscape(this); });
}

Helios::Window::~Window()
{
    
}

void Helios::Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Helios::Window::keyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    Helios::Input::keyEvent(instance, key, action);
}

void Helios::Input::defaultEscape(Window* window)
{
    glfwSetWindowShouldClose(window->m_GLFWinstance, true);
}

void Helios::Input::keyEvent(Window* window, int key, int action)
{
    if (action == GLFW_PRESS)
    {
        onKeyPress(window, key);
    }
    else if (action == GLFW_RELEASE)
    {
        onKeyRelease(window, key);
    }
    else if (action == GLFW_REPEAT)
    {
        onKeyHold(window, key);
    }
}

void Helios::Input::addKeyPressBinding(Window* window, int key, const Callback callback)
{
    window->m_KeyPressCallbacks.insert({ key, callback });
}

void Helios::Input::addKeyReleaseBinding(Window* window, int key, const Callback callback)
{
    window->m_KeyReleaseCallbacks.insert({key, callback});
}

void Helios::Input::addKeyHoldBinding(Window* window, int key, const Callback callback)
{
    window->m_KeyHoldCallbacks.insert({ key, callback });
}

void Helios::Input::removeKeyPressBinding(Window* window, int key)
{
    window->m_KeyPressCallbacks.erase(key);
}

void Helios::Input::removeKeyReleaseBinding(Window* window, int key)
{
    window->m_KeyReleaseCallbacks.erase(key);
}

void Helios::Input::removeKeyHoldBinding(Window* window, int key)
{
    window->m_KeyHoldCallbacks.erase(key);
}

void Helios::Input::swapKeyPressBinding(Window* window, int formerKey, int newKey)
{
    Callback callback = window->m_KeyPressCallbacks.at(formerKey);
    Helios::Input::removeKeyPressBinding(window, formerKey);
    Helios::Input::addKeyPressBinding(window, newKey, callback);
}

void Helios::Input::swapKeyReleaseBinding(Window* window, int formerKey, int newKey)
{
    Callback callback = window->m_KeyReleaseCallbacks.at(formerKey);
    Helios::Input::removeKeyReleaseBinding(window, formerKey);
    Helios::Input::addKeyReleaseBinding(window, newKey, callback);
}

void Helios::Input::swapKeyHoldBinding(Window* window, int formerKey, int newKey)
{
    Callback callback = window->m_KeyHoldCallbacks.at(formerKey);
    Helios::Input::removeKeyHoldBinding(window, formerKey);
    Helios::Input::addKeyHoldBinding(window, newKey, callback);
}

void Helios::Input::onKeyPress(Window* window, int key)
{
    std::invoke(window->m_KeyPressCallbacks[key]);
}

void Helios::Input::onKeyRelease(Window* window, int key)
{
    std::invoke(window->m_KeyReleaseCallbacks[key]);
}

void Helios::Input::onKeyHold(Window* window, int key)
{
    std::invoke(window->m_KeyHoldCallbacks[key]);
}