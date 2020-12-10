/**\file renderCommands.cpp*/

#include "engine_pch.h"
#include "rendering/renderCommands.h"
#include "rendering/renderAPI.h"
#include "glad/glad.h"

namespace Engine
{


	std::function<void(void)> RenderCommandFactory::getClearDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {glClear(GL_DEPTH_BUFFER_BIT); };
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}


	std::function<void(void)> RenderCommandFactory::getClearColourBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {glClear(GL_COLOR_BUFFER_BIT); };
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}


	std::function<void(void)> RenderCommandFactory::getClearColourAndDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); };
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}


	std::function<void(void)> RenderCommandFactory::getEnableDepthTestCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {glEnable(GL_DEPTH_TEST); };
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}


	std::function<void(void)> RenderCommandFactory::getEnableBlendCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {glEnable(GL_BLEND); };
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}


	std::function<void(void)> RenderCommandFactory::getSetBlendFuncDefault()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandFactory::disableDepthTestCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {glDisable(GL_DEPTH_TEST); };
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandFactory::disableBlendCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() {glDisable(GL_BLEND);};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}


	std::function<void(void)> RenderCommandFactory::getSetClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return [r, g, b, a]() {glClearColor(r, g, b, a);};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandFactory::useProgramCommand(uint32_t shaderID)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return [shaderID]() {glUseProgram(shaderID); };
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}






}