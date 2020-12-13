/**\file GLFWInputPoller.h*/

#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \class GLFWInputPoller
	** \brief Input poller for getting the current keyboard/mouse state specific to the GLFW system
	*/
	class GLFWInputPoller
	{

	private:
		static GLFWwindow* s_window; //!< Current GLFW window

	public:
		static bool isKeyPressed(int32_t keyCode); //!< is a key pressed and which key 
		static bool isMouseButtonPressed(int32_t mouseButton);  //!< is a mouse button pressed
		static glm::vec2 getMousePos(); //!< get the cursos location

		static void setCurrentWindow(GLFWwindow* newWindow) { s_window = newWindow; } //!< Set the current window  


	};

}