/** \file renderCommands*/

#pragma once

#include <functional>


namespace Engine
{

	class RendererCommon;
	class RenderCommand
	{
	private:
		std::function<void(void)> m_action; //!< Action of the render command
		friend class RenderCommandFactory;
		friend class RendererCommon;

	public:
		enum class Commands{clearDepthBuffer, clearColourBuffer, clearColourAndDepthBuffer, setClearColour};
	
	};


	class RenderCommandFactory
	{

	private:
		static std::function<void(void)> getClearColourAndDepthBufferCommand();
	
	public:
		static RenderCommand * createCommand(RenderCommand::Commands command)
		{
			RenderCommand* result = new RenderCommand;
			
			
			switch (command)
			{
			case RenderCommand::Commands::clearColourAndDepthBuffer:
				result->m_action = getClearColourAndDepthBufferCommand();
				return result;

			}
		}
	};


}