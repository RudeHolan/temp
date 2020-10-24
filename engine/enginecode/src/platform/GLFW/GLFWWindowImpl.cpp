/*\file GLFWWindowImpl.cpp*/

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"
#include "systems/log.h"

namespace Engine {

#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWWindowImpl(properties);
	}
#endif


	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties& properties)
	{
		init(properties);
	}

	void GLFWWindowImpl::init(const WindowProperties& properties)
	{
		m_props = properties;

		m_aspectRatio = static_cast<float>(m_props.m_width) / static_cast<float>(m_props.m_height);

		if (m_props.m_isFullscreen) {
			// NEEDS IMPLEMENTATION
		}
		else
		{
			m_native = glfwCreateWindow(m_props.m_width, m_props.m_height,m_props.m_title, nullptr , nullptr);
		}
	}

	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_native);

	}
	void GLFWWindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents();
	}

	void GLFWWindowImpl::setVSync(bool VSync)
	{
		m_props.m_isVSync = VSync;

		if (VSync) {

			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

	}


}