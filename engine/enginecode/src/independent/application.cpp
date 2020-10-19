/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"
#include "events/events.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}


		// Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();


		// Start timer
		m_timer.reset(new ChronoTimer);
		m_timer->start();
	}



	Application::~Application()
	{

		// Stop log
		m_logSystem->stop();
	}


	void Application::run()
	{

		float timestep = 0.f;
		float accumulatedTime = 0.f;

		while (m_running)
		{
				timestep = m_timer->getElapsedTime();
				m_timer->reset();
				//Log::trace("FPS {0}", 1.0f / timestep);

				accumulatedTime += timestep;
				if (accumulatedTime > 5.f)
				{
					WindowCloseEvent close();
					WindowResizeEvent resize(800, 600);
					// Handle this 

				}
				

		};
	}

}
