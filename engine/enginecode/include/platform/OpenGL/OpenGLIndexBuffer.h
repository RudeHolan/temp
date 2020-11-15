/*\ file OpenGLIndexBuffer.h */
#pragma once

#include <cstdint>
#include "rendering/indexBuffer.h"
namespace Engine
{
	/**\class OpenGLIndexBuffer
    * This class creates an OpenGL Index Buffer
    */


	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t m_openGL_ID; //!< Render ID
		uint32_t m_count; //!< Effective draw count

	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count); //!< Constructor
		virtual ~OpenGLIndexBuffer(); //!< Virtual distructor
		virtual inline uint32_t getRenderID() const override { return m_openGL_ID; } //!< Get the render ID
		virtual inline uint32_t getCount() const override { return m_count; } //!< Get the effective draw count
	};


}
