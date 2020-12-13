/*\file renderAPI.h*/

#pragma once

namespace Engine
{
	/**
    \class RenderAPI 
	** \brief This class sets up the API 
    */
	class RenderAPI
	{

	public:
		enum class API { None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3}; //!< The different type of API's
		inline static API getAPI() { return s_API; } //!< Get the API

	private:
		static API s_API; //!< The API in use
	};
}
