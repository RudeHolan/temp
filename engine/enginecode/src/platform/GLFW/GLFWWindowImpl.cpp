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
			m_native = glfwCreateWindow(m_props.m_width, m_props.m_height, m_props.m_title, glfwGetPrimaryMonitor(), nullptr);
		}
		else
		{
			m_native = glfwCreateWindow(m_props.m_width, m_props.m_height,m_props.m_title, nullptr , nullptr);
		}

		glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler));


		// Setting the callbacks
		glfwSetWindowCloseCallback(m_native,
			[](GLFWwindow* window)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onClose = handler->m_getOnWindowCloseCallback();
			WindowCloseEvent e;
			onClose(e);
		}
		);


		glfwSetWindowSizeCallback(m_native,
			[](GLFWwindow* window, int newWidth, int newHeight)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onResize = handler->m_getOnWindowResizeCallback();
			WindowResizeEvent e(newWidth, newHeight);
			onResize(e);
		}
		);

		glfwSetKeyCallback(m_native,
			[](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS) {
				auto& onKeyPress = handler->m_getOnKeyPressCallback();
				KeyPressEvent e(keyCode, 0);
				onKeyPress(e);
			}
			else if (action == GLFW_REPEAT)
			{
				auto& onKeyPress = handler->m_getOnKeyPressCallback();
				KeyPressEvent e(keyCode, 1);
				onKeyPress(e);
			}
			else if (action == GLFW_RELEASE)
			{
				auto& onKeyRelease = handler->m_getOnKeyReleaseCallback();
				KeyReleaseEvent e(keyCode);
				onKeyRelease(e);
			}


		}
		);

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