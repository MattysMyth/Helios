#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	initGLFW();
    initGLAD();

    // Create a Shader Program
    createShader();
    // Initialize a Vertex Array Object
    vao = new VAO();
    // Initialize a Vertex Buffer Object
    vbo = new VBO();
    // Initialize a Index Buffer Object
    ibo = new IBO();

}

Engine::~Engine()
{
    delete vbo;
    delete ibo;
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

void Engine::render()
{
    // Run the main render loop
    while (!glfwWindowShouldClose(m_window))
    {
        // Clear current buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw call
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

        // Swap the buffers
        glfwSwapBuffers(m_window);

        // Poll and process events
        glfwPollEvents();
    }
}

void Engine::loadEntities(std::vector<Entity*> entities)
{
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;
    unsigned int indexOffset = 0;

    for (Entity* entity : entities)
    {
        verticies.insert(verticies.end(), entity->verticies.begin(), entity->verticies.end());

        for (unsigned int index : entity->indices)
        {
            indices.push_back(index + indexOffset);
        }

        indexOffset = indexOffset + entity->verticies.size();
    }

    vbo->update(verticies);
    ibo->update(indices);

    indexCount = indices.size();
}