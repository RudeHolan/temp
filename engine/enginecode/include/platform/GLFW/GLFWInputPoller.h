/**\file GLFWInputPoller.h*/

#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/* \class GLFWInputPoller
	*   Input poller for getting the current keyboard/mouse state specific to the GLFW system
	*/
	class GLFWInputPoller
	{

	private:
		static GLFWwindow* s_window; //!< Current GLFW window

	public:
		static bool isKeyPressed(int32_t keyCode);
		static bool isMouseButtonPressed(int32_t mouseButton);
		static glm::vec2 getMousePos();

		static void setCurrentWindow(GLFWwindow* newWindow) { s_window = newWindow; }


	};

}