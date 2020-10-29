/**\file inputPoller.h*/

#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	/* \class InputPoller
	*   API agnostic input poller for getting the current keyboard/mouse state
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode);
		static bool isMouseButtonPressed(int32_t mouseButton);
		static glm::vec2 getMousePos();
		inline static float getMouseX() { return getMousePos().x; }
		inline static float getMouseY() { return getMousePos().y; }

		static void setNativeWindow(void* nativeWindow);

	};

}