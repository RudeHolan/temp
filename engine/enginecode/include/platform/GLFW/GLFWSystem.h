/**\file GLFWSystem.h */

#pragma once

#include "systems/system.h"

#include "systems/log.h"

#include <GLFW/glfw3.h>


namespace Engine
{
	/**\class GLFWSystem
	** \brief Starts the glfw system
	*/
	class GLFWSystem : public System 
	{
		virtual void start(SystemSignal init = SystemSignal::None, ...) override
		{
			auto errorCode = glfwInit();
			if (!errorCode) 
			{
				Log::error("Cannot initialize GLFW: {0}", errorCode);
			}
		} //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override
		{
			glfwTerminate();
		}//!< Stop the system
	};
}