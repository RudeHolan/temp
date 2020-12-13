/**\file inputPoller.h*/

#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	/** \class InputPoller
	** \brief API agnostic input poller for getting the current keyboard/mouse state
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is a key pressed
		static bool isMouseButtonPressed(int32_t mouseButton);//!< is a mouse button pressed
		static glm::vec2 getMousePos(); //!< get the mouse position
		inline static float getMouseX() { return getMousePos().x; } //!< get the mouse position x coordinate
		inline static float getMouseY() { return getMousePos().y; }//!< get the mouse position y coordinate

		static void setNativeWindow(void* nativeWindow); //!< set the native window

	};

}