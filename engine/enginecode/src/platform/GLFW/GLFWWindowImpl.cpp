/*\file GLFWWindowImpl.cpp*/

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"
#include "platform/GLFW/GLFW_OpenGL_GC.h"
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

		m_graphicsContext.reset(new GLFW_OpenGL_GC(m_native));
		m_graphicsContext->init();

		glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler));


		// Setting the window callbacks
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

		glfwSetWindowPosCallback(m_native,
			[](GLFWwindow* window, int posX, int posY)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onWindowMove = handler->m_getOnWindowMoveCallback();
			WindowMoveEvent e(posX, posY);
			onWindowMove(e);
		}
		);

		glfwSetWindowFocusCallback(m_native,
			[](GLFWwindow* window, int focused)
		{			
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			if (focused) {
				auto& onFocus = handler->m_getOnWindowFocusCallback();
				WindowFocusEvent e(focused);
				onFocus(e);
			}
			else
			{
				auto& lostFocus = handler->m_getOnWindowLostFocusCallback();
				WindowLostFocusEvent e(focused);
				lostFocus(e);
			}
		}
		);


		// Setting the key callbacks
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

		glfwSetCharCallback(m_native,
			[](GLFWwindow* window, unsigned int codepoint)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onKeyType = handler->m_getOnKeyTypeCallback();
			KeyTypeEvent e(codepoint);
			onKeyType(e);
		}
		);


		//Setting the mouse callbacks
		glfwSetMouseButtonCallback(m_native,
			[](GLFWwindow* window, int button, int action, int mods)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS)
			{
				auto& onButtonPress = handler->m_getOnMouseButtonPressCallback();
				MouseButtonPressEvent e(button);
				onButtonPress(e);
			}
			else if (action == GLFW_RELEASE)
			{
				auto& onButtonRelease = handler->m_getOnMouseButtonReleaseCallback();
				MouseButtonReleaseEvent e(button);
				onButtonRelease(e);
			}
		}
		);

		glfwSetScrollCallback(m_native,
			[](GLFWwindow* window, double xOffset, double yOffset)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onScroll = handler->m_getOnMouseScrollCallback();
			MouseScrollEvent e(xOffset, yOffset);
			onScroll(e);
		}
		);

		glfwSetCursorPosCallback(m_native,
			[](GLFWwindow* window, double posX, double posY)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onMove = handler->m_getOnMouseMoveCallback();
			MouseMoveEvent e(posX, posY);
			onMove(e);
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
		m_graphicsContext->swapBuffers();
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