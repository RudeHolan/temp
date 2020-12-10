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
		enum class Commands{
			//commands with no args
			clearDepthBuffer, clearColourBuffer, clearColourAndDepthBuffer, 
			enableDepthTest, enableBlend, setBlendFuncDefault,
			disableDepthTest, disableBlend,
			
			// commands with args
			setClearColour, useProgram
		};
	
	};


	class RenderCommandFactory
	{

	private:
		// Following code based on https://www.geeksforgeeks.org/how-to-iterate-over-the-elements-of-an-stdtuple-in-c/
		template <typename G, size_t I, typename... Ts>
		typename std::enable_if<I >= sizeof...(Ts),void>::type
		static getValue(G& result, std::tuple<Ts...> tup)
		{
			// if index is great than or equal tuple size dont do anything
		}
		template <typename G, size_t I, typename... Ts>
		typename std::enable_if<(I < sizeof...(Ts)),void>::type
		static getValue(G& result, std::tuple<Ts...> tup)
		{
			// Get the Ith thing in the tuple
			result = std::get<I>(tup);
		}

		static std::function<void(void)> getClearDepthBufferCommand();
		static std::function<void(void)> getClearColourBufferCommand();
		static std::function<void(void)> getClearColourAndDepthBufferCommand();

		static std::function<void(void)> getEnableDepthTestCommand();
		static std::function<void(void)> getEnableBlendCommand();
		static std::function<void(void)> getSetBlendFuncDefault();

		static std::function<void(void)> disableDepthTestCommand();
		static std::function<void(void)> disableBlendCommand();




		static std::function<void(void)> getSetClearColourCommand(float r, float g, float b, float a);
		static std::function<void(void)> useProgramCommand(uint32_t shaderID);


	public:
		template<typename ...Args> static RenderCommand * createCommand(RenderCommand::Commands command, Args&& ...args)
		{
			RenderCommand* result = new RenderCommand;
			
			
			switch (command)
			{

				//0 args commands
				//
				//disableDepthTest, disableBlend,

			case RenderCommand::Commands::clearDepthBuffer:
				result->m_action = getClearDepthBufferCommand();
				return result;

			case RenderCommand::Commands::clearColourBuffer:
				result->m_action = getClearColourBufferCommand();
				return result;

			case RenderCommand::Commands::clearColourAndDepthBuffer:
				result->m_action = getClearColourAndDepthBufferCommand();
				return result;

			case RenderCommand::Commands::enableDepthTest:
				result->m_action = getEnableDepthTestCommand();
				return result;

			case RenderCommand::Commands::enableBlend:
				result->m_action = getEnableBlendCommand();
				return result;

			case RenderCommand::Commands::setBlendFuncDefault:
				result->m_action = getSetBlendFuncDefault();
				return result;

			case RenderCommand::Commands::disableBlend:
				result->m_action = disableBlendCommand();
				return result;

			case RenderCommand::Commands::disableDepthTest:
				result->m_action = disableDepthTestCommand();
				return result;


				//Commands with args
				//
				//
			case RenderCommand::Commands::setClearColour :
			{
				float r, g, b, a;

				auto argTuple = std::make_tuple(args...);

				getValue<float, 0>(r, argTuple);
				getValue<float, 1>(g, argTuple);
				getValue<float, 2>(b, argTuple);
				getValue<float, 3>(a, argTuple);
				result->m_action = getSetClearColourCommand(r, g, b, a);
			}
				return result;


			case RenderCommand::Commands::useProgram:
			{
				uint32_t shaderID;

				auto argTuple = std::make_tuple(args...);

				getValue<uint32_t, 0>(shaderID, argTuple);
				result->m_action = useProgramCommand(shaderID);
			}
				return result;


				

			}
		}
	};


}