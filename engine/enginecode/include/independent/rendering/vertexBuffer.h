/*\file vertexBuffer.h*/

#pragma once

#include <cstdint>
#include "rendering/bufferLayout.h"

namespace Engine
{
	/**\class VertexBuffer
	* API agnostic vertex buffer
	*/

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default; //!< Virtual distructor
		virtual inline uint32_t getRenderID() const = 0; //!< Get the render ID
		virtual const VertexBufferLayout& getLayout() const = 0; //!< Get the layout
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) = 0; //!< Edit the vertex buffer
		
		static VertexBuffer* create(void* vertices, uint32_t size, const VertexBufferLayout& bufferLayout); //!< Create the vertex buffer
	};


}