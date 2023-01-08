#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <map>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace Helios
{
	// Object to handle GLFW instances and input functionality
	class Window
	{
		using Callback = std::function<void()>;

	public:
		Window();
		~Window();

		/*
		Pointer to an instance of a GLFW Window
		*/
		GLFWwindow* m_GLFWinstance;

		/*
		Map of all bound key press functions and associated keys
		*/
		std::map<int, Callback> m_KeyPressCallbacks;

		/*
		Map of all bound key release functions and associated keys
		*/
		std::map<int, Callback> m_KeyReleaseCallbacks;

		/*
		Map of all bound key hold functions and associated keys
		*/
		std::map<int, Callback> m_KeyHoldCallbacks;

	private:
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

	namespace Input
	{
		using Callback = std::function<void()>;

		void defaultEscape(Window* window);

		/*
		Adds a binding between a given functionand the key pressed. When pressed, GLFW will register the event and when polled will
		call the bound function
		*/
		void addKeyPressBinding(Window* window, int key, const Callback callback);

		/*
		Adds a binding between a given functionand the key released. When released, GLFW will register the event and when polled will
		call the bound function
		*/
		void addKeyReleaseBinding(Window* window, int key, const Callback callback);

		/*
		Adds a binding between a given functionand the key held. When held, GLFW will register the event and when polled will
		call the bound function
		*/
		void addKeyHoldBinding(Window* window, int key, const Callback callback);

		/*
		Removes any key press function binding on the given key
		*/
		void removeKeyPressBinding(Window* window, int key);

		/*
		Removes any key release function binding on the given key
		*/
		void removeKeyReleaseBinding(Window* window, int key);

		/*
		Removes any key hold function binding on the given key
		*/
		void removeKeyHoldBinding(Window* window, int key);

		/*
		Swaps the key associated with a bound key press function
		*/
		void swapKeyPressBinding(Window* window, int formerKey, int newKey);

		/*
		Swaps the key associated with a bound key release function
		*/
		void swapKeyReleaseBinding(Window* window, int formerKey, int newKey);

		/*
		Swaps the key associated with a bound key hold function
		*/
		void swapKeyHoldBinding(Window* window, int formerKey, int newKey);

		/*
		Executes bound functions for pressed keys
		*/
		void onKeyPress(Window* window, int key);

		/*
		Executes bound functions for released keys
		*/
		void onKeyRelease(Window* window, int key);

		/*
		Executes events for held down keys
		*/
		void onKeyHold(Window* window, int key);

		/*
		Determines whether the key event is for a pressed, released or held key and calls
		the associated function
		*/
		void keyEvent(Window* window, int key, int action);
	}
}

#endif // !WINDOW_H