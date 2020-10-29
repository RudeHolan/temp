/*\file inputPoller.cpp*/
#include "engine_pch.h"
#include "core/inputPoller.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWInputPoller.h"
#endif

namespace Engine {

	bool InputPoller::isKeyPressed(int32_t keyCode)
	{
		return GLFWInputPoller::isKeyPressed(keyCode);
	}

	bool InputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		return GLFWInputPoller::isMouseButtonPressed(mouseButton);
	}

	glm::vec2 InputPoller::getMousePos()
	{
		return GLFWInputPoller::getMousePos();
	}

	void InputPoller::setNativeWindow(void* nativeWindow)
	{
		GLFWInputPoller::setCurrentWindow(reinterpret_cast<GLFWwindow*>(nativeWindow));
	}

}