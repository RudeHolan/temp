/*\ file OpenGLIndexBuffer.h */
#pragma once

#include <cstdint>

namespace Engine
{
	class OpenGLIndexBuffer
	{
	private:
		uint32_t m_openGL_ID; //!< Render ID
		uint32_t m_count; //!< Effective draw count

	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		inline uint32_t getRenderID() const { return m_openGL_ID; }
		inline uint32_t getCount() const { return m_count; }
	};


}
