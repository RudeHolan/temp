/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "timer.h"
#include "events/events.h"
#include "events/eventHandler.h"
#include "core/window.h"
#include "core/inputPoller.h"
#include "cameras/cameraController.h"
#include "core/layer.h"
#include "core/layerStack.h"
#include "rendering/rendererCommon.h"


namespace Engine {

	/**
	\class Application
	** \brief Fundemental class of the engine. A singleton which runs the game loop infinitely.
	*/

	struct ApplicationProps
	{
		WindowProperties winProps;
		uint32_t batchsize2D = 8192;
		const char* fontFilePath = "./assets/fonts/arial.ttf";
		uint32_t charSize = 86;
		uint32_t shadersCapacity = 40;
		uint32_t texturesCapacity = 30;
	};

	class Application
	{
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?	

	protected:
		Application(); //!< Constructor
		std::shared_ptr<Log> m_logSystem; //!< Log system
		std::shared_ptr<System> m_windowsSystem; //!< Window system
		std::shared_ptr<CameraController> m_camController; //!< Camera controller

		std::shared_ptr<ITimer> m_timer; //!< Timer
		std::shared_ptr<Window> m_window; //!< Window

		LayerStack m_layerStack;


		bool onClose(WindowCloseEvent& e); //!< Run when the window closes
		bool onResize(WindowResizeEvent& e); //!< Run when the window is resized
		bool onWindowMove(WindowMoveEvent& e); //!< Run when the window is moved
		bool onFocus(WindowFocusEvent& e); //!< Run when the window is focused
		bool onLostFocus(WindowLostFocusEvent& e); //!< Run the window isn't focused

		bool onKeyPress(KeyPressEvent& e); //!< Run when a key is pressed
		bool onKeyRelease(KeyReleaseEvent& e); //!< Run when a key is released
		//bool onKeyType(KeyTypeEvent& e); //!< Run when a text is typed

		bool onButtonPress(MouseButtonPressEvent& e); //!< Run when a mouse button is pressed
		bool onButtonRelease(MouseButtonReleaseEvent& e); //!< Run when a mouse button is released
		bool onScroll(MouseScrollEvent& e); //!< Run when the mouse scroll is used
		bool onMouseMove(MouseMoveEvent& e); //!< Run when the mouse is moved

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline std::shared_ptr<Window>& getWindow() { return m_window; } //!< Get the window
		void run(); //!< Main loop
		
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}