#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	initGLFW();
	initGLAD();

    Vertex vert1, vert2, vert3;

    vert1.position.x = -0.5f;
    vert1.position.y = -0.5f;
    
    vert2.position.x = 0.0f;
    vert2.position.y = 0.5f;

    vert3.position.x = 0.5f;
    vert3.position.y = -0.5f;

    std::vector<Vertex> verticies;
    verticies.push_back(vert1);
    verticies.push_back(vert2);
    verticies.push_back(vert3);

    std::vector<unsigned int> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    // Create a Shader Program
    createShader();
    // Initialize a Vertex Array Object
    createVertexArray();
    // Initialize a Vertex Buffer Object
    vbo = new VBO(verticies);
    // Initialize a Index Buffer Object
    ibo = new IBO(indices);

    // Run the main render loop
    while (!glfwWindowShouldClose(m_window))
    {
        // Clear current buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw call
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

bool Engine::createShader()
{
    Shader vertexShader("../Engine/src/Shader/BasicVertex.shader", ShaderType::VERTEX);

    Shader fragmentShader("../Engine/src/Shader/BasicFragment.shader", ShaderType::FRAGMENT);

    // link shaders to a program
    unsigned int shaderProgram = glCreateProgram();
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