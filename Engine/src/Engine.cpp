#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	initGLFW();
	initGLAD();
    float positions[] =
    {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    createShader();
    createVertexArray();
    createVertexBuffer(positions);
    createIndexBuffer(indices);

    while (!glfwWindowShouldClose(m_window))
    {
        // Draw code
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Swap the buffers
        glfwSwapBuffers(m_window);

        // Poll and process events
        glfwPollEvents();
    }

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
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    return true;
}

bool Engine::createVertexBuffer(float positions[])
{
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    return true;
}

bool Engine::createIndexBuffer(unsigned int indices[])
{
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    return true;
}

bool Engine::createShader()
{
    Shader vertexShader;
    vertexShader.createShader("../Engine/src/Shader/BasicVertex.shader", ShaderType::VERTEX);

    Shader fragmentShader;
    fragmentShader.createShader("../Engine/src/Shader/BasicFragment.shader", ShaderType::FRAGMENT);

    // link shaders to a program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.getID());
    glAttachShader(shaderProgram, fragmentShader.getID());
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);
    // check for linking errors
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(shaderProgram, length, &length, message);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << message << std::endl;
    }

    // Delete Shader objects as we've compiled and linked the program
    glDeleteShader(vertexShader.getID());
    glDeleteShader(fragmentShader.getID());

    glUseProgram(shaderProgram);

    return true;
}

void Engine::testPrint()
{
	std::cout << "Hello World" << std::endl;
}