#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <map>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

// Object to handle GLFW instances and input functionality
class Window
{
    using Callback = std::function<void()>;

public:
	Window();
	~Window();

	/*
	Adds a binding between a given functionand the key pressed. When pressed, GLFW will register the event and when polled will  
	call the bound function
	*/
	void addBinding(int key, const Callback callback);

	/*
	Removes any function binding on the given key
	*/
	void removeBinding(int key);

	/*
	Swaps the key associated with a bound function
	*/
	void swapBinding(int formerKey, int newKey);

	/*
	Executes bound functions for pressed keys
	*/
	void onKeyPress(int key);

	/*
	Executes bound functions for released keys
	*/
	void onKeyRelease(int key);

	/*
	Executes events for held down keys
	*/
	void onKeyHold(int key);

	/*
	Determines whether the key event is for a pressed, released or held key and calls
	the associated function
	*/
	void keyEvent(int key, int action);

	/*
	Pointer to an instance of a GLFW Window
	*/
	GLFWwindow* m_instance;

private:
	/*
	Map of all bound functions and associated keys
	*/
    std::map<int, Callback> m_Callbacks;

	/*
	Window width, default value set to 800 pixels
	*/
	unsigned int m_SCREEN_WIDTH = 800;

	/*
	Window height, default value set to 600 pixels
	*/
	unsigned int m_SCREEN_HEIGHT = 600;

	/*
	Boolean value representing Fullscreen or windowed. If TRUE, application will run windowed
	with the dimensions defined by m_SCREEN_WIDTH and m_SCREEN_HEIGHT. If FALSE, will 
	run full screen with monitor dimensions
	*/
	bool m_windowedMode = true;

	/*
	Function to be called on Window resize
	*/
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	/*
	Function to be called on key event
	*/
	static void keyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // !WINDOW_H