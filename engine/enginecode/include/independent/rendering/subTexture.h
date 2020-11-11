/*\ file subTexture.h*/

#pragma once

#include "platform/OpenGL/OpenGLTexture.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
	class SubTexture
	{
	private:
		std::shared_ptr<OpenGLTexture> m_texture;
		glm::vec2 m_UVStart;
		glm::vec2 m_UVEnd;
		glm::ivec2 m_size; //!< Size in pixels

	public:
		SubTexture();   //!< default constructor
		SubTexture(const std::shared_ptr<OpenGLTexture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd);
		inline glm::vec2 getUVStart() { return m_UVStart; }
		inline glm::vec2 getUVEnd() { return m_UVEnd; }
		glm::ivec2 getSize() { return m_size; } //!< get the size
		glm::vec2 getSizef() { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; } //!< Get the size(in vec2)
		inline uint32_t getWidth() { return m_size.x; } //!< Get the width
		inline uint32_t getHeight() { return m_size.y; } //!< Get the height 
		inline uint32_t getWidthf() { return static_cast<float>(m_size.x); } //!< Get the width in float
		inline uint32_t getHeightf() { return static_cast<float>(m_size.y); } //!< Get the height in float
		float transformU(float U); //!< Transform original to atlased co-ords
		float transformV(float V);
		glm::vec2 transformUV(glm::vec2 UV);
	
	
	};


}
