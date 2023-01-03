#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader/Shader.h"
#include "Renderer/Vertex.h"
#include "Renderer/VBO.h"
#include "Renderer/IBO.h"
#include "Renderer/VAO.h"
#include "Entity/Entity.h"
#include "../Window.h"

/*
Engine is the object responsible for running all Rendering, Physics, Lighting, Sound, etc.The purpose is
to seperate any code necessary to execute the graphics and computing calculations from the game logic
and game data stored and handled in the application.
*/
class Engine
{
	// Screen sizes, default values set at 800 x 600
	unsigned int m_SCREEN_WIDTH = 800;
	unsigned int m_SCREEN_HEIGHT = 600;

	unsigned int indexCount;
	unsigned int matrixID;

	glm::mat4 mvp;

	VAO* vao;
	VBO* vbo;
	IBO* ibo;

	Window* window;

	bool m_windowedMode = true;

	// Sets glViewport with given width and height. Used as a function to be called on resize
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	static void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

	// Initialize GLAD for OpenGL calls
	bool initGLAD();

public:

	/*
	Engine constructor. Will initialize a main GLFW window and load GLAD to be used for OpenGL calls.
	Important for inital GLFW and GLAD load order to be controlled otherwise GLAD will not load correctly.
	*/
	Engine();
	~Engine();

	// Initialize Shader
	bool createShader();

	void render();

	/*
	Takes a vector of all entities to be loaded into the Vertex Buffer and Index Buffer on the GPU
	*/
	void loadEntities(std::vector<Entity*> entities);

};

#endif // !ENGINE_H
