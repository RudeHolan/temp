/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}


		// Start Log
		m_logSystem.reset(new Log);
		m_logSystem->start();





	}



	Application::~Application()
	{

		// Stop log
		m_logSystem->stop();
	}


	void Application::run()
	{
		while (m_running)
		{
				Log::debug("Hello world! {0} {1}", 1, "Look at all the colors");
				Log::error("Hello world!  {0} {1}", 1, "Look at all the colors");
				Log::info("Hello world!  {0} {1}", 1, "Look at all the colors");
				Log::trace("Hello world!  {0} {1}", 1, "Look at all the colors");
				Log::warn("Hello world!  {0} {1}", 1, "Look at all the colors");
				Log::release("Hello world!  {0} {1}", 1, "Look at all the colors");

		};
	}

}
