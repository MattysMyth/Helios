#include "Engine.h"
#include <iostream>

Engine::Engine()
{
    // Initialize a Window using GLFW
    window = new Helios::Window();
    // Load GLAD for OpenGL function calls
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

    // Orthographic view from the camera (Projection)
    glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);

    // Camera Matrix (View)
    glm::mat4 view(1.0f);

    // Model Matrix (Model)
   glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, -4.0f, 0.0f));

    mvp = projection * view * model;

    matrixID = glGetUniformLocation(shaderProgram, "mvp");

    return true;
}

void Engine::render()
{
    // Run the main render loop
    while (!glfwWindowShouldClose(window->m_GLFWinstance))
    {
        // Clear current buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Send mvp matrix to the Shader on the GPU
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

        // Draw call
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

        // Swap the buffers
        glfwSwapBuffers(window->m_GLFWinstance);

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