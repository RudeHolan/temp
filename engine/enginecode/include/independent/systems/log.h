/**\file log.h*/

#pragma once

#include "system.h"
#include <spdlog/spdlog.h>

namespace Engine

{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_consoleLogger; //!< Console logger


	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...); //!< Start the logger
		virtual void stop(SystemSignal close = SystemSignal::None, ...); //!< Stop the logger

		template <class ...Args>
		static void debug(Args&& ... args);

		template <class ...Args>
		static void error(Args&& ... args);

		template <class ...Args>
		static void info(Args&& ... args);

		template <class ...Args>
		static void trace(Args&& ... args);

		template <class ...Args>
		static void warn(Args&& ... args);

		template <class ...Args>
		static void release(Args&& ... args);
	};


	template<class ...Args>
	static void Log::debug(Args&& ...args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->debug(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Log::error(Args&& ...args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->error(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Log::info(Args&& ...args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->info(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Log::trace(Args&& ...args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->trace(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Log::warn(Args&& ...args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->warn(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Log::release(Args&& ...args)
	{
		s_consoleLogger->trace(std::forward<Args>(args) ...);
	}



}