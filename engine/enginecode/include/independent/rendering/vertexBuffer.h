/*\file vertexBuffer.h*/

#pragma once

#include <cstdint>
#include "rendering/bufferLayout.h"

namespace Engine
{
	/**\class VertexBuffer
	* API agnostic vertex buffer (interface class)
	*/

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default; //!< Destroy the vertex buffer
		virtual inline uint32_t getRenderID() const = 0; //!< Get the render ID
		virtual const BufferLayout& getLayout() const = 0; //!< Get the layout
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) = 0; //!< Edit the vertex buffer
		
		static VertexBuffer* create(void* vertices, uint32_t size, BufferLayout bufferLayout); //!< Create the vertex buffer
	};


}