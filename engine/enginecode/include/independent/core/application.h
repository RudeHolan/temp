/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "timer.h"
#include "events/events.h"
#include "events/eventHandler.h"
#include "core/window.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?	

	protected:
		Application(); //!< Constructor
		std::shared_ptr<Log> m_logSystem; //!< Log system
		std::shared_ptr<System> m_windowsSystem; //!< Window system

		std::shared_ptr<ITimer> m_timer; //!< Timer
		std::shared_ptr<Window> m_window; //!< Window

		EventHandler m_handler; //!< This is the event handler

		bool onClose(WindowCloseEvent& e); //!< Run when the window closes

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}