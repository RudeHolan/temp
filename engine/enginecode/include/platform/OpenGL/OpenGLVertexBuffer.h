/*\file OpenGLVertexBuffer.h*/
#pragma once

#include "rendering/bufferLayout.h" 
#include "rendering/vertexBuffer.h"

namespace Engine
{

	/**\class OpenGLVertexBuffer
	* This class creates an OpenGL Vertex Buffer
	*/

	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		BufferLayout m_layout; //!< The buffer layout

	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout bufferLayout); //!< Constructor
		virtual ~OpenGLVertexBuffer(); //!< Virtual distructor
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) override; //!< Edit the vertex buffer
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Get the render ID
		virtual const BufferLayout& getLayout() const override { return m_layout; } //!< Get the layout
	};
}