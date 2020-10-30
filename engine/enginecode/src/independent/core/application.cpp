/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>

#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif


namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}


		// Start logging system
		m_logSystem.reset(new Log);
		m_logSystem->start();


		// Start windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();


		// Start timer (not a system)
		m_timer.reset(new ChronoTimer);
		m_timer->start();


		// Create a window
		WindowProperties props("My Game Engine", 1920, 1080, false);
		m_window.reset(Window::create(props));


		m_window->getEventHandler().setOnWindowCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMoveCallback(std::bind(&Application::onWindowMove, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowFocusCallback(std::bind(&Application::onFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1));

		m_window->getEventHandler().setOnKeyPressCallback(std::bind(&Application::onKeyPress, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleaseCallback(std::bind(&Application::onKeyRelease, this, std::placeholders::_1));
		//m_window->getEventHandler().setOnKeyTypeCallback(std::bind(&Application::onKeyType, this, std::placeholders::_1));

		m_window->getEventHandler().setOnMouseButtonPressCallback(std::bind(&Application::onButtonPress, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonReleaseCallback(std::bind(&Application::onButtonRelease, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseScrollCallback(std::bind(&Application::onScroll, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseMoveCallback(std::bind(&Application::onMouseMove, this, std::placeholders::_1));

		InputPoller::setNativeWindow(m_window->getNativeWindow());

		m_timer->reset();
	}



	bool Application::onClose(WindowCloseEvent & e)
	{
		e.handle(true);
		m_running = false;
		return e.isHandled();
	}


	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		auto& size = e.getSize();
		//Log::info("Window resizeed info - size X: {0}; size Y: {1}", size.x, size.y);
		return e.isHandled();
	}

	bool Application::onWindowMove(WindowMoveEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		//Log::info("Window moved (new position) info - new pos X: {0}; new pos Y: {1}", pos.x, pos.y);
		return e.isHandled();
	}

	bool Application::onFocus(WindowFocusEvent& e)
	{
		e.handle(true);
		auto focus = e.getFocus();
		//Log::info("Window focused: {0} (should be 1)", focus);
		return e.isHandled();
	}

	bool Application::onLostFocus(WindowLostFocusEvent& e)
	{
		e.handle(true);
		auto focus = e.getFocus();
		//Log::info("Window lost focus: {0} (should be 0)", focus);
		return e.isHandled();
	}


	bool Application::onKeyPress(KeyPressEvent& e)
	{
		e.handle(true);
		auto keyCode = e.getKeyCode();
		auto repeatCount = e.getRepeatCount();
		//Log::info("Key pressed info - Key code: {0}; Repeat count: {1}", keyCode, repeatCount);
		return e.isHandled();
	}


	bool Application::onKeyRelease(KeyReleaseEvent& e)
	{
		e.handle(true);
		auto keyCode = e.getKeyCode();
		if (keyCode == 96) {
			system("cls");
			//Log::info("Key released info - Key code: {0} (console is cleared)", keyCode);
		}
		else
		{
			//Log::info("Key released info - Key code: {0}", keyCode);
		}
		return e.isHandled();
	}

	/*bool Application::onKeyType(KeyTypeEvent& e)
	{
		e.handle(true);
		auto codePoint = e.getKeyCode();
		Log::info("Key typed info - Code point: {0}", codePoint);
		return e.isHandled();
	}*/

	bool Application::onButtonPress(MouseButtonPressEvent& e)
	{
		e.handle(true);
		auto button = e.getButton();
		//Log::info("Mouse button pressed info - Key code: {0}", button);
		return e.isHandled();
	}

	bool Application::onButtonRelease(MouseButtonReleaseEvent& e)
	{
		e.handle(true);
		auto button = e.getButton();
		//Log::info("Mouse button released info - Key code: {0}", button);
		return e.isHandled();
	}

	bool Application::onScroll(MouseScrollEvent& e)
	{
		e.handle(true);
		auto offX = e.getOffsetX();
		auto offY = e.getOffsetY();
		//Log::info("Mouse Scroll info - X offset: {0}; Y offset: {1}", offX, offY);
		return e.isHandled();
	}

	bool Application::onMouseMove(MouseMoveEvent& e)
	{
		e.handle(true);
		auto posX = e.getX();
		auto posY = e.getY();
		//Log::info("Mouse position info - X possition: {0}; Y possition:{1}", posX, posY); 
		return e.isHandled();
	}


	Application::~Application()
	{

		// Stop logging system
		m_logSystem->stop();

		// Stop window system
		m_windowsSystem->stop();
	}


	void Application::run()
	{

		float timestep = 0.f;
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		while (m_running)
		{
				timestep = m_timer->getElapsedTime();
				m_timer->reset();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				if (InputPoller::isKeyPressed(65)) Log::error("A is pressed");
				if (InputPoller::isMouseButtonPressed(0)) Log::error("Left mouse button is pressed");

				m_window->onUpdate(timestep);
				
		};
	}
		
}
