#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <map>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

// Object to handle GLFW instances and functionality
class Window
{
    using Callback = std::function<void()>;

public:
	Window();
	~Window();

	void addBinding(int key, const Callback callback);
	void removeBinding(int key);
	void swapBinding(int formerKey, int newKey);

	void onKeyPress(int key);
	void onKeyRelease(int key);
	void onKeyHold(int key);

	void keyEvent(int key, int action);

	GLFWwindow* m_instance;

private:
    std::map<int, Callback> m_Callbacks;

	// Screen sizes, default values set at 800 x 600
	unsigned int m_SCREEN_WIDTH = 800;
	unsigned int m_SCREEN_HEIGHT = 600;

	bool m_windowedMode = true;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void keyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // !WINDOW_H