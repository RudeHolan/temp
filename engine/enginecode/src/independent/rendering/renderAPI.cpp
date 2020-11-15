/*file renderAPI.cpp*/

#include "engine_pch.h"
#include "systems/log.h"

#include "rendering/renderAPI.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"

#include "rendering/indexBuffer.h"
#include "rendering/vertexBuffer.h"
#include "rendering/vertexArray.h"


namespace Engine
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None :
			Log::error("Not having a rendering API is not supported");
			break;


		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
			break;


		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not supported");
			break;


		case RenderAPI::API::Vulkan:
			Log::error("Vulkan is not supported");
			break;
		}

		return nullptr;
	}

	VertexBuffer* VertexBuffer::create(void* vertices, uint32_t size, BufferLayout bufferLayout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("Not having a rendering API is not supported");
			break;


		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, bufferLayout);
			break;


		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not supported");
			break;


		case RenderAPI::API::Vulkan:
			Log::error("Vulkan is not supported");
			break;
		}

		return nullptr;
	}

	VertexArray* VertexArray::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("Not having a rendering API is not supported");
			break;


		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
			break;


		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not supported");
			break;


		case RenderAPI::API::Vulkan:
			Log::error("Vulkan is not supported");
			break;
		}

		return nullptr;
	}


}
